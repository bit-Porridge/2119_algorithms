#include <iostream>
#include <vector>
using namespace std;

struct Matrix {
    int rows;
    int cols;
    vector<vector<int>> data; // Use vector for dynamic array

    // Constructor to initialize the matrix with given dimensions
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}

    // Function to access elements of the matrix
    int& operator()(int i, int j) {
        return data[i][j];
    }

    // Function to multiply two matrices
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions do not match for multiplication.");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result(i, j) = 0;
                for (int k = 0; k < cols; k++) {
                    result(i, j) += data[i][k] * other.data[k][j];
                }
            }
        }
        return result; // Return by value (temporary object)
    }

    // Function to raise a matrix to the power n
    Matrix fastpow(int n) {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; ++i) {
            res(i, i) = 1; // Initialize the result matrix as the identity matrix I
        }
        Matrix x = *this; // Use the current matrix as base
        while (n) {
            if (n & 1) res = res * x; // LSB is 1, multiply the result by x
            x = x * x;
            n >>= 1; // Right shift n by 1
        }
        return res;
    }
};

// Fibonacci function using matrix exponentiation
int fib(int n) {
    Matrix T(2, 2);
    T(0, 0) = 1; T(0, 1) = 1; T(1, 0) = 1; T(1, 1) = 0; 
    if (n == 0) return 0; // Handling the case for n = 0
    if (n == 1) return 1; // Handling the case for n = 1
    Matrix base(2, 1);
    base(0, 0) = 1;
    base(1, 0) = 1;  
    T = T.fastpow(n - 2);
    Matrix ans = T * base;
    return ans(0, 0);
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    cout << "The " << n << "th Fibonacci number is: " << fib(n) << endl;
    return 0;
}
