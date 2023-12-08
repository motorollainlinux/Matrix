#include <iostream>
#include <exception>
#include <math.h>
#include <vector>
#include "Matrix.h"

Matrix::Matrix() {
    M = (double**)calloc(1, sizeof(double*));
    M[0] = (double*)calloc(1, sizeof(double));
    colums = 1;
    rows = 1;
}
Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    colums = other.colums;
    M = other.M;
}
Matrix::Matrix(int rows, int colums) { // colums - столбцы , rows - строки;
    if(colums <= 0 || rows <= 0)
    throw std::out_of_range("Exception: colums or/and row can`t be eqwal or lowwer zero.");
    else{
        this->colums = colums;
        this->rows = rows;
        M = (double**)calloc(rows, sizeof(double*));
        for(int i = 0; i < rows; i++) {
            M[i] = (double*)calloc(colums, sizeof(double));
        }
    }
}
Matrix::~Matrix() {
    colums = 0;
    rows = 0;
    M = nullptr;
}
void Matrix::MatrixSetter(int r, int c, double num) {
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
    double RandomNum = 0;
    for( int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            RandomNum = rand()%10;
            M[i][j] = RandomNum;
        }
    }
}
double Matrix::MatrixDeterminant() {
    if(colums == rows) {
        if(rows == 2) 
        return M[0][0]*M[1][1]-M[0][1]*M[1][0];
        else {
            double result = 0;
            int mi = 0, mj = 0;
            for(int i = 0; i < rows; i++) {
                Matrix Minor(rows-1, rows-1);
                for(int j = 0; j < rows; j++) {
                    for(int k = 0; k < rows; k++) {
                        if(j != 0 && k != i) {
                            Minor.MatrixSetter(mi, mj, M[j][k]);
                            mj++;
                            if(mj > Minor.rows-1) {
                                mj = 0;
                                mi++;
                            }
                        }
                    }
                }
                mi = 0;
                mj = 0;
                result += pow(-1, i+2) * M[0][i] * Minor.MatrixDeterminant();
            }
            return result;
        }
    } else 
    throw std::out_of_range("Det func Exception: imposible to determenant matrix whis not eqvals numbers of colums and rows.");
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
Matrix Matrix::AlgCompliments() {
    if(colums == rows) {
        Matrix result(rows, colums);
        int mi = 0, mj = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < rows; j++) {
                Matrix Minor(rows-1, rows-1);
                for(int k = 0; k < rows; k++) {
                    for(int n = 0; n < rows; n++) {
                        if(k != i && n != j) {
                            Minor.MatrixSetter(mi, mj, M[k][n]);
                            mj++;
                            if(mj > Minor.rows-1) {
                                mj = 0;
                                mi++;
                            }
                        }
                    }
                }
                mi = 0;
                mj = 0;
                result.MatrixSetter(i, j, pow(-1, (i+1)+(j+1)) * Minor.MatrixDeterminant());
                result = result.MatrixTransponent();
            }
        }
        return result;
    } else 
    throw std::out_of_range("AlgCompliment func Exception: imposible to determenant matrix whis not eqvals numbers of colums and rows.");
}
Matrix Matrix::InverseMatrix() {
    Matrix Complements = this->AlgCompliments();
    double determinant = this->MatrixDeterminant();
    if(determinant == 0)
    throw std::out_of_range("Exeption: Can`t find inverse matrix when determinant eqval 0.");
    Matrix result = Complements * (1/determinant);
    return result;
}
void Matrix::operator=(Matrix OderMatrix) {
    for (int i = 0; i < rows; i++) {
        delete [] M[i];
    }
    rows = OderMatrix.rows;
    colums = OderMatrix.colums;
    M = (double**)calloc(rows, sizeof(double*));
    for(int i = 0; i < rows; i++) {
        M[i] = (double*)calloc(colums, sizeof(double));
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
    int Summ = 0;
    if(colums == OderMatrix.rows && rows == OderMatrix.colums) {
        Matrix result(rows, OderMatrix.colums);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < OderMatrix.colums; j++) {
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
Matrix Matrix::operator*(double num) {
    Matrix result(rows, colums);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            result.MatrixSetter(i, j, M[i][j]*num);
        }
    }
    return result;
}
Matrix Matrix::operator/(double num) {
    Matrix result(rows, colums);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < colums; j++) {
            result.MatrixSetter(i, j, M[i][j]/num);
        }
    }
    return result;
}
Matrix Matrix::operator+(Matrix& OderMatrix) {
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
    // srand(time(NULL));
    

    // Matrix A(5, 5);
    // A.RandFillMatrix();
    // A.OutPutMatrix();
    // Matrix B = A.InverseMatrix();
    // B.OutPutMatrix();

    // Matrix A(5, 5);
    // A.RandFillMatrix();
    // A.OutPutMatrix();
    // Matrix B;
    // B = A.AlgCompliments();
    // std::cout << "det1:                                     " << B.MatrixDeterminant() << "\n";
    // B.OutPutMatrix();
    
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
    
    // Matrix A(5, 5);
    // A.RandFillMatrix();
    // A.OutPutMatrix();
    // double res = A.MatrixDeterminant();
    // std::cout << "Determenant: " << res << "\n"; 
    
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
