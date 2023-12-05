class Matrix {
    // private:
    public:
    int **M;
    int colums, rows;
    protected:
    void GetInf(int& c, int& r);
    int** GetMatrixInfo();
    public:
    Matrix();
    Matrix(int rows, int colums);
    Matrix(const Matrix &other);
    ~Matrix();
    void MatrixSetter(int c, int r, int num);
    int MatrixGetter(int c, int r);
    void OutPutMatrix();
    void FillMatrix();
    void FillMatrix(int num);
    void RandFillMatrix();
    Matrix MatrixTransponent();
    int MatrixDeterminant();
    void operator=(Matrix OderMatrix);
    bool operator==(Matrix OderMatrix);
    Matrix operator*(Matrix& OderMatrix);
    Matrix operator*(int num);
    Matrix operator+(Matrix& OderMatrix);
    Matrix operator-(Matrix& OderMatrix);
};
