#pragma once

class Matrix {
    public:
    int nrows;
    int ncols;
    float** val;

    Matrix(int nrows, int ncols);
    ~Matrix();

    void display();
    void exchange_rows(int i, int j);
    void scale(int i, float value);
    void scale_and_add(int i, int j, float scale);

};
