//
// Created by Theo Lincke on 1/20/24.
//

#ifndef MATLIBCPP_MATRIX_H
#define MATLIBCPP_MATRIX_H

#include <array>
#include <sstream>

template<typename T, std::size_t R, std::size_t C>
class Matrix {
public:
    Matrix() = default;

    explicit Matrix(const std::array<std::array<double, C>, R> &_data)
            : data(_data) {}

    std::array<T, C> &operator[](std::size_t i) {
        return data[i];
    }

    const std::array<T, C> &operator[](std::size_t i) const {
        return data[i];
    }

    friend std::ostream &operator<<(std::ostream &os, Matrix<T, R, C> const &tc) {
        return os << tc.print();
    }

    Matrix<T, R, C> &operator*=(const T &x);

    Matrix<T, R, C> operator*(const T &x) const;

    template<std::size_t K>
    Matrix<T, R, K> operator*(const Matrix<T, C, K> &x) const;

    Matrix<T, R, C> &operator*=(const Matrix<T, C, C> &x);

    Matrix<T, R, C> operator+(const T &x) const;

    Matrix<T, R, C> &operator+=(const T &x);

    Matrix<T, R, C> operator+(const Matrix<T, R, C> &x) const;

    Matrix<T, R, C> &operator+=(const Matrix<T, R, C> &x);

    Matrix<T, R, C> operator-(const T &x) const;

    Matrix<T, R, C> &operator-=(const T &x);

    Matrix<T, R, C> operator-(const Matrix<T, R, C> &x) const;

    Matrix<T, R, C> &operator-=(const Matrix<T, R, C> &x);

    Matrix<T, R, C> &operator=(const Matrix<T, R, C> &x);

    bool operator==(const Matrix<T, R, C> &x) const;

    template<typename Z, size_t M, size_t N>
    friend bool nearEqual(const Matrix<Z, M, N> &left, const Matrix<Z, M, N> &right, Z epsilon);

private:
    std::array<std::array<T, C>, R> data;

    [[nodiscard]] std::string print() const;
};

template<typename T, size_t M, size_t N, size_t K>
Matrix<T, M, K> matMul(const Matrix<T, M, N> &left, const Matrix<T, N, K> &right);

template<typename T, size_t R, size_t C>
void scalMul_inline(Matrix<T, R, C> &left, const T &right);

template<typename T, size_t R, size_t C>
void matAdd_inline(Matrix<T, R, C> &left, const Matrix<T, R, C> &right);

template<typename T, size_t R, size_t C>
void scalAdd_inline(Matrix<T, R, C> &left, const T &right);

template<typename T, size_t R, size_t C>
void matSub_inline(Matrix<T, R, C> &left, const Matrix<T, R, C> &right);

template<typename T, size_t R, size_t C>
void scalSub_inline(Matrix<T, R, C> &left, const T &right);


#include "algorithms.tpp"
#include "operators.tpp"
#include "utilities.tpp"

#endif //MATLIBCPP_MATRIX_H
