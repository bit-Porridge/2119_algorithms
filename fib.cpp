#include <iostream>
using namespace std;

struct Matrix {
    int rows;
    int cols;
    int **data; // Dynamic array to store matrix elements

    // Constructor to initialize the matrix with given dimensions
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0; // Initialize matrix elements to 0
            }
        }
    }

    // Destructor to free memory
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Function to access elements of the matrix
    int& operator()(int i, int j) {
        return data[i][j];
    }

    // Function to multiply two matrices
    Matrix operator*(Matrix& other) {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions do not match for multiplication.");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result(i, j) = 0;
                for (int k = 0; k < cols; k++) {
                    result(i, j) += data[i][k] * other(k, j); 
                }
            }
        }
        return result;
    }

    // Function to raise a matrix to the power n
    Matrix fastpow(int n) {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; ++i) {
            res(i, i) = 1; // Initialize the result matrix as the identity matrix I
        }
        Matrix x = *this; // Use the current matrix as base, x is a copy of the structure object
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
