#include <iostream>
#include <exception>
#include <math.h>
#include "Matrix.h"

Matrix::Matrix() {
    *M = (int*)calloc(1, sizeof(int));
    M = (int**)calloc(1, sizeof(int));
    colums = 1;
    rows = 1;
}
Matrix::Matrix(int colums, int rows) { // colums - столбцы , rows - строки;
    if(colums <= 0 || rows == 0)
    throw std::out_of_range("Exception: colums or/and row can`t be eqwal or lowwer zero.");
    else{
        this->colums = colums;
        this->rows = rows;
        *M = (int*)calloc(rows, sizeof(int));
        for(int i = 0; i < rows; i++) {
            M = (int**)calloc(colums, sizeof(int));
        }
    }
}
Matrix::~Matrix() {
    free(M);
}
void Matrix::GetInf(int& c, int& r) {
    c = colums;
    r = rows;
}
void Matrix::MatrixSetter(int c, int r, int num) {
    if(c < colums && c >= 0 && r < rows && r >= 0)
    M[c][r] = num;
    else 
    throw std::range_error("Exception: can`t set number matrix of inposible colums or/and rows.");
}
int Matrix::MatrixGetter(int c, int r) {
    if(c < colums && c >= 0 && r < rows && r >= 0)
    return M[c][r];
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
    Matrix TransponentMatrix(rows, colums);
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
            int AlgebraicComplement[colums];
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
bool Matrix::operator==(Matrix OderMatrix) {
    bool IsCorrect = true;
    try{
        for(int i = 0; i < colums; i++) {
            for(int j = 0; j < rows; j++) {
                if(M[i][j] != OderMatrix.MatrixGetter(i, j))
                IsCorrect = false;
            }
        }
    } catch(...) {
        IsCorrect = false;
    }
    return IsCorrect;
}
Matrix Matrix::operator*(Matrix& OderMatrix) {
    int OderColums, OderRows, Summ = 0;
    OderMatrix.GetInf(OderColums, OderRows);
    if(colums == OderRows && rows == OderColums) {
        Matrix result(colums, colums);
        int resitercolum = 0, resiterrows = 0;
        for(int i = 0; i < colums; i++) {
            for(int j = 0; j < rows; j++) {
            Summ += M[i][j]*OderMatrix.MatrixGetter(j,i);
            }
            result.MatrixSetter(resitercolum, resiterrows, Summ);
            Summ = 0;
            resitercolum++;
            if(resitercolum == colums) {
                resitercolum = 0;
                resiterrows++;
            }  
        }
        return result;
    } else
    throw std::out_of_range("Exception: imposible multiply matrix on matrix if not eqvals colums of first matrix and rows of second matrix.");
}
Matrix Matrix::operator*(int num) {
    Matrix result(colums, rows);
    for(int i = 0; i < colums; i++) {
        for(int j = 0; j < rows; j++) {
            result.MatrixSetter(i, j, M[i][j]*num);
        }
    }
    return result;
}
Matrix Matrix::operator+(Matrix& OderMatrix) {
    int OderColums, OderRows;
    OderMatrix.GetInf(OderColums, OderRows);
    if(colums == OderColums && rows == OderRows) {
        Matrix result(colums, rows);
        for(int i = 0; i < colums; i++) {
            for(int j = 0; j < rows; j++) {
                result.MatrixSetter(i, j, M[i][j]+OderMatrix.MatrixGetter(j,i));
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
        Matrix result(colums, rows);
        for(int i = 0; i < colums; i++) {
            for(int j = 0; j < rows; j++) {
                result.MatrixSetter(i, j, M[i][j]-OderMatrix.MatrixGetter(j,i));
            }
        }
        return result;
    } else
    throw std::out_of_range("Exception: imposible substract matrix of matrix if not eqvals colums/rows of first matrix and colums/rows of second matrix.");
}
int main() {
    Matrix A(5,5), B(5,5);
    // A.RandFillMatrix();
    // B.RandFillMatrix();
    A.OutPutMatrix();
    B.OutPutMatrix();
    // Matrix C = A * B;
    // C.OutPutMatrix();
    return 0;
}
