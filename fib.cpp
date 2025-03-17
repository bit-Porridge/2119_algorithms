#include <iostream>
using namespace std;


struct Matrix {
    int rows;
    int cols;
    int **data; //dynamic array to store matrix elements

    // Constructor to initialize the matrix with given dimensions
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
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
        Matrix result(rows, other.cols);
        for (int i=0;i<rows;i++){
            for (int j=0;j<other.cols;j++){
                result(i,j)=0;
                for (int k=0;k<cols;k++){
                    result(i,j)+=result(i,k)*other(k,j);
                }
            }
        }return result;
    }

    /**
     * Function to raise a matrix to the power n
     * should only include sqaure matrices
     */
    Matrix fastpow(Matrix x, int n) {
        Matrix res = Matrix(rows, cols);
        for (int i=0; i<rows;++i){
            res(i,i)=1;           // Initialize the result matrix as the identity matrix I
        }
        while (n) {
            if (n & 1) res = res * x;     //LSB is 1, multiply the result by x 
            x = x * x;           
            n >>= 1;                      // Right shift n by 1
            } return res;
    }
};
//[f(n),f(n-1)]=[1,1;1,0]*[f(n-1),f(n-2)]=[1,1;1,0]^(n-2)*[f(2),f(1)]=[1,1;1,0]^(n-2)*[1,1]
int fib(int n){
    Matrix T(2,2);
    T(0,0)=1; T(0,1)=1; T(1,0)=1; T(1,1)=0; 
    Matrix base = Matrix(2,1);
    base(0,0)=1;
    base(1,0)=1;  
    T = T.fastpow(T,n-2);
    Matrix ans = T*base;
    return ans(0,0);
}

int main(){
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    cout << "The " << n << "th Fibonacci number is: " << fib(n) << endl;
}
