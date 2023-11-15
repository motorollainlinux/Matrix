class Matrix {
    private:
    int **M;
    int colums, rows;
    public:
    Matrix();
    Matrix(int colums, int rows);
    ~Matrix();
    void OutPutMatrix();
    void FillMatrix();
    void FillMatrix(int num);
    void RandFillMatrix();
    Matrix MatrixTransponent();
    double MatrixDeterminant();
    Matrix operator==(Matrix OderMatrix);
    Matrix operator*(Matrix& OderMatrix);
    Matrix operator*(int num);
    Matrix operator+(Matrix& OderMatrix);
    Matrix operator-(Matrix& OderMatrix);
};