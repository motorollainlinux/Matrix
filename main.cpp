#include <iostream>
#include <exception>
#include "Matrix.h"

Matrix::Matrix() {
    *M = (int*)calloc(1, sizeof(int));
    M = (int**)calloc(1, sizeof(int));
    colums = 1;
    rows = 1;
}
Matrix::Matrix(int colums, int rows) { // colums - столбцы , rows - строки;
    if(colums <= 0 || rows == 0)
    throw std::range_error("Exception: colums or/and row can`t be eqwal or lowwer zero.");
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
Matrix::OutPutMatrix() {
    
}
int main() {
    return 0;
}
