#ifndef MATRIX_H
#define MATRIX_H

template <class T>
class Vector {
    protected:
        const int dimension;
    public:

};

template <class T> class SparseVector;
template <class T> class DenseVector;

template <class T>
class SparseVector : public Vector<T> {
    private:
    public:
};

template <class T>
class DenseVector : public Vector<T> {
    private:
    public:
};

template <class T>
class Matrix {
    protected:
        const int rows;
        const int columns;
    public:
        virtual void set_value(int i, int j, T val) = 0;
        virtual T get_value(int i, int j) const = 0;
};

template <class T> class SparseMatrix;
template <class T> class DenseMatrix;

template <class T>
class SparseMatrix : public Matrix<T> {
    private:
    public:
};

template <class T>
class DenseMatrix : public Matrix<T> {
    private:
        T *data;
    public:

};

template <class T> SparseMatrix<T> *compress(DenseMatrix<T> &A);
template <class T> DenseMatrix<T> *decompress(SparseMatrix<T> &A);

#endif
