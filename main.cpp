#include <iostream>
#include <exception>
#include <math.h>
#include <vector>
#include "Matrix.h"

Matrix::Matrix() {
    // M = new int*[1];
    // M[0] = new int[1]; 
    M = (int**)calloc(1, sizeof(int*));
    M[0] = (int*)calloc(1, sizeof(int));
    colums = 1;
    rows = 1;
}
Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    colums = other.colums;
    M = other.M;
}
Matrix::Matrix(int rows, int colums) { // colums - столбцы , rows - строки;
    if(colums <= 0 || rows == 0)
    throw std::out_of_range("Exception: colums or/and row can`t be eqwal or lowwer zero.");
    else{
        // std::cout<< "hdskjhfkjdsjha\n";
        this->colums = colums;
        this->rows = rows;
        // M = new int*[rows];
        // for(unsigned i; i < colums; i++) {
        //     M[i] = new int[colums];
        // }
        M = (int**)calloc(rows, sizeof(int*));
        for(int i = 0; i < rows; i++) {
            M[i] = (int*)calloc(colums, sizeof(int));
        }
    }
}
Matrix::~Matrix() {
    colums = 0;
    rows = 0;
    // delete[] M;
    M = nullptr;
}
void Matrix::GetInf(int& r, int& c) {
    r = rows;
    c = colums;
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
        if(rows == 2) {
            double result = M[0][0]*M[1][1]-M[0][1]*M[1][0];
            return result;
        } else {
            std::vector<double> AlgebraicCompements(rows);
            int mi = 0, mj = 0;
            for(int i = 0; i < rows; i++) {
                Matrix Minor(rows-1, rows-1);
                for(int j = 0; j < rows; j++) {
                    for(int k = 0; k < rows; k++) {
                        if(j != i && k != i) {
                            Minor.MatrixSetter(mi, mj, M[j][k]);
                            mi++;
                            if(mi == rows) {
                                mi = 0;
                                mj++;
                            }
                        }
                    }
                }
                mi = 0;
                mj = 0;
                Minor.OutPutMatrix();
                AlgebraicCompements[i] = Minor.MatrixDeterminant();
            }
            double result = 0;
            for(int i = 0; i < rows; i++) {
                result += M[0][i]*AlgebraicCompements[i];
            }
            return result;
        }
    } else 
    throw std::out_of_range("Exception: imposible to determenant matrix whis not eqvals numbers of colums and rows.");
}
void Matrix::operator=(Matrix OderMatrix) {
    int OderRows, OderColums;
    OderMatrix.GetInf(OderRows, OderColums);
    for (int i = 0; i < rows; i++) {
        delete [] M[i];
    }
    rows = OderRows;
    colums = OderColums;
    M = new int*[rows];
    for(int i = 0; i < rows; i++) {
        M[i] = new int[colums];
    }
    // M = (int**)calloc(rows, sizeof(int*));
    // for(int i = 0; i < rows; i++) {
    //     M[i] = (int*)calloc(colums, sizeof(int));
    // }
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
        Matrix result(rows, OderMatrix.colums);
        // /* test */ result.OutPutMatrix();
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < OderColums; j++) {
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
    // int OderColums, OderRows;
    // OderMatrix.GetInf(OderColums, OderRows);
    if(colums == OderMatrix.colums && rows == OderMatrix.rows) {
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
    // int OderColums, OderRows;
    // OderMatrix.GetInf(OderColums, OderRows);
    if(colums == OderMatrix.colums && rows == OderMatrix.rows) {
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
    srand(time(NULL));
    
    
    // Matrix A(4, 5);
    // Matrix B(4, 5);
    // A.RandFillMatrix();
    // A.OutPutMatrix();
    // B.RandFillMatrix();
    // B.OutPutMatrix();
    // Matrix C = A-B;
    // Matrix D = A+B;
    // C.OutPutMatrix();
    // D.OutPutMatrix();
    
    // Matrix A(5, 5);
    // Matrix B(5, 5);
    // A.FillMatrix(5);
    // // A.RandFillMatrix();
    // A.OutPutMatrix();
    // B.FillMatrix(5);
    // // B.RandFillMatrix();
    // B.OutPutMatrix();
    // if(A == B)
    // std::cout << "eqvals!!!\n";
    // else
    // std::cout << "not eqvals(\n";
    
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    Matrix A(5, 5);
    A.RandFillMatrix();
    A.OutPutMatrix();
    int res = A.MatrixDeterminant();
    std::cout << "Determenant: " << res << "\n"; 
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    
    // Matrix A(3, 4);
    // A.RandFillMatrix();
    // A.OutPutMatrix();
    // Matrix B = A.MatrixTransponent();
    // B.OutPutMatrix();
    
    // Matrix A(4, 5);
    // Matrix B(5, 4);
    // A.RandFillMatrix();
    // B.RandFillMatrix();
    // std::cout << "A:\n";
    // A.OutPutMatrix();
    // std::cout << "B:\n";
    // B.OutPutMatrix();
    // Matrix C = A * B;
    // std::cout << "A * B =\n";
    // C.OutPutMatrix();
    
    
    // Matrix B(5, 5);
    // Matrix C(5, 5);
    // B.RandFillMatrix();
    // C.RandFillMatrix();
    // Matrix A = B*C;
    // A.OutPutMatrix();
    std::cout << "done\n";
    return 0;
}
