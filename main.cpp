#include <iostream>
#include <exception>
#include <math.h>
#include <vector>
#include "Matrix.h"

Matrix::Matrix() {
    M = (int**)calloc(1, sizeof(int*));
    M[0] = (int*)calloc(1, sizeof(int));
    colums = 1;
    rows = 1;
}
Matrix::Matrix(int rows, int colums) { // colums - столбцы , rows - строки;
    if(colums <= 0 || rows == 0)
    throw std::out_of_range("Exception: colums or/and row can`t be eqwal or lowwer zero.");
    else{
        this->colums = colums;
        this->rows = rows;
        M = (int**)calloc(rows, sizeof(int*));
        for(int i = 0; i < colums; i++) {
            M[i] = (int*)calloc(colums, sizeof(int));
        }
    }
}
Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete [] M[i];
    }
    delete [] M;
}
void Matrix::GetInf(int& c, int& r) {
    c = colums;
    r = rows;
}
int** Matrix::GetMatrixInfo() {
    return M;
}
void Matrix::MatrixSetter(int r, int c, int num) {
    if(c < colums && c >= 0 && r < rows && r >= 0)
    M[r][c] = num;
    else 
    throw std::range_error("Exception: can`t set number matrix of inposible colums or/and rows.");
}
int Matrix::MatrixGetter(int r, int c) {
    if(c < colums && c >= 0 && r < rows && r >= 0)
    return M[r][c];
    else 
    throw std::range_error("Exception: can`t get number matrix of inposible colums or/and rows.");
}
void Matrix::OutPutMatrix() {
    for( int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            std::cout << M[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
void Matrix::FillMatrix() {
    for( int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            M[i][j] = 0;
        }
    }
}
void Matrix::FillMatrix(int num) {
    for( int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            M[i][j] = num;
        }
    }
}
void Matrix::RandFillMatrix() {
    int RandomNum = 0;
    for( int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            RandomNum = rand()%10;
            M[i][j] = RandomNum;
        }
    }
}
Matrix Matrix::MatrixTransponent() {
    Matrix TransponentMatrix(colums, rows);
    for( int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            TransponentMatrix.MatrixSetter(j, i, M[i][j]);
        }
    }
    return TransponentMatrix;
}
int Matrix::MatrixDeterminant() {
    if(colums == rows) {
        int result = 0;
        if(colums == 2) {
            result = M[0][0]*M[1][1] - M[0][1]*M[1][0];
            return result;
        } else {
            Matrix Minor(colums-1, rows-1);
            int minoritercolums = 0, minoriterrows = 0;
            std::vector<int>  AlgebraicComplement(colums);
            for(int i = 0; i < colums; i++) {
                for(int j = 0; j < colums; j++) {
                    for(int k = 0; k < rows; k++) {
                        if(k != i && j != i) {
                            Minor.MatrixSetter(minoritercolums, minoriterrows, M[j][k]);
                            minoritercolums++;
                            if(minoritercolums == colums) {
                                minoritercolums = 0;
                                minoriterrows++;
                            }
                        }
                    }
                }
                AlgebraicComplement[i] = pow(-1,2*i) * Minor.MatrixDeterminant();
            }
            for(int i = 0; i < colums; i++) {
                result += M[i][i]*AlgebraicComplement[i];
            }
            return result;
        }
    } else 
    throw std::out_of_range("Exception: imposible to determenant matrix whis not eqvals numbers of colums and rows.");
}
void Matrix::operator=(Matrix OderMatrix) {
    int OderRows, OderColums;
    OderMatrix.GetInf(OderRows, OderColums);
    rows = OderRows;
    colums = OderColums;
    M = (int**)calloc(rows, sizeof(int*));
    for(int i = 0; i < colums; i++) {
        M[i] = (int*)calloc(colums, sizeof(int));
    }
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            M[i][j] = OderMatrix.MatrixGetter(i, j);
        }
    }
}
bool Matrix::operator==(Matrix OderMatrix) {
    bool IsCorrect = true;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            if(M[i][j] != OderMatrix.MatrixGetter(i, j))
            IsCorrect = false;
        }
    }
    return IsCorrect;
}
Matrix Matrix::operator*(Matrix& OderMatrix) {
    int OderColums, OderRows, Summ = 0;
    OderMatrix.GetInf(OderRows, OderColums);
    if(colums == OderRows && rows == OderColums) {
        Matrix result(rows, rows);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < rows; j++) {
                for(int k = 0; k < colums; k++) {
                    Summ += M[i][k]*OderMatrix.MatrixGetter(k, j);
                }
                result.MatrixSetter(i, j, Summ);
                Summ = 0;
            }
        }
        return result;
    } else
    throw std::out_of_range("Exception: imposible multiply matrix on matrix if not eqvals colums of first matrix and rows of second matrix.");
}
Matrix Matrix::operator*(int num) {
    Matrix result(rows, colums);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            result.MatrixSetter(i, j, M[i][j]*num);
        }
    }
    return result;
}
Matrix Matrix::operator+(Matrix& OderMatrix) {
    int OderColums, OderRows;
    OderMatrix.GetInf(OderColums, OderRows);
    if(colums == OderColums && rows == OderRows) {
        Matrix result(rows, colums);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < colums; j++) {
                result.MatrixSetter(i, j, M[i][j]+OderMatrix.MatrixGetter(i,j));
            }
        }
        return result;
    } else
    throw std::out_of_range("Exception: imposible add matrix to matrix if not eqvals colums/rows of first matrix and colums/rows of second matrix.");
}
Matrix Matrix::operator-(Matrix& OderMatrix) {
    int OderColums, OderRows;
    OderMatrix.GetInf(OderColums, OderRows);
    if(colums == OderColums && rows == OderRows) {
        Matrix result(rows, colums);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < colums; j++) {
                result.MatrixSetter(i, j, M[i][j]-OderMatrix.MatrixGetter(i, j));
            }
        }
        return result;
    } else
    throw std::out_of_range("Exception: imposible substract matrix of matrix if not eqvals colums/rows of first matrix and colums/rows of second matrix.");
}
int main() {
    Matrix A(4, 5), B(5, 5);
    A.RandFillMatrix();
    B.RandFillMatrix();
    std::cout << "A:\n";
    A.OutPutMatrix();
    std::cout << "B:\n";
    B.OutPutMatrix();
    Matrix C = A * B;
    std::cout << "A * B =\n";
    C.OutPutMatrix();
    std::cout << "done\n"; 
    
    // Matrix A(3, 3), B(5, 5);
    // A = B;
    // A.OutPutMatrix();
    return 0;
}
