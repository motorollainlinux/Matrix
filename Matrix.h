class Matrix {
    private:
    int **M;
    int colums, rows;
    protected:
    void GetInf(int& c, int& r);
    public:
    Matrix();
    Matrix(int colums, int rows);
    ~Matrix();
    void MatrixSetter(int c, int r, int num);
    int MatrixGetter(int c, int r);
    void OutPutMatrix();
    void FillMatrix();
    void FillMatrix(int num);
    void RandFillMatrix();
    Matrix MatrixTransponent();
    int MatrixDeterminant();
    bool operator==(Matrix OderMatrix);
    Matrix operator*(Matrix& OderMatrix);
    Matrix operator*(int num);
    Matrix operator+(Matrix& OderMatrix);
    Matrix operator-(Matrix& OderMatrix);
};
