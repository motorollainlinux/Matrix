class Matrix {
    protected:
    double **M;
    int colums, rows;
    // void GetInf(int& c, int& r);
    // double** GetMatrixInfo();
    public:
    Matrix();
    Matrix(int rows, int colums);
    Matrix(const Matrix &other);
    ~Matrix();
    void MatrixSetter(int c, int r, double num);
    int MatrixGetter(int c, int r);
    void OutPutMatrix();
    void FillMatrix();
    void FillMatrix(int num);
    void RandFillMatrix();
    double MatrixDeterminant();
    Matrix MatrixTransponent();
    Matrix AlgCompliments();
    Matrix InverseMatrix();
    void operator=(Matrix OderMatrix);
    bool operator==(Matrix OderMatrix);
    Matrix operator*(Matrix& OderMatrix);
    Matrix operator*(double num);
    Matrix operator/(double num);
    Matrix operator+(Matrix& OderMatrix);
    Matrix operator-(Matrix& OderMatrix);
};
