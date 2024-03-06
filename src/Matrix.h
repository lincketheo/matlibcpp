//
// Created by Theo Lincke on 1/20/24.
//

#ifndef MATLIBCPP_MATRIX_H
#define MATLIBCPP_MATRIX_H

#include <array>
#include <sstream>
#include <valarray>

template<typename P, std::size_t R, std::size_t C>
class Matrix {
public:
    Matrix();

    explicit Matrix(const std::array<std::array<P, C>, R> &_data);

    Matrix(const Matrix &rhs);

    std::valarray<P> &operator[](std::size_t i) {
        if (isTranspose) {
            return data[std::slice(i * C, C, 1)];
        } else {
            return data[std::slice(i, R, C)];
        }
    }

    std::valarray<P> operator[](std::size_t i) const {
        if (isTranspose) {
            return data[std::slice(i * C, C, 1)];
        } else {
            return data[std::slice(i, R, C)];
        }
    }

    friend std::ostream &operator<<(std::ostream &os, Matrix<P, R, C> const &tc) {
        return os << tc.print();
    }

    Matrix<P, R, C> &operator*=(const P &x);

    Matrix<P, R, C> operator*(const P &x) const;

    template<std::size_t K>
    Matrix<P, R, K> operator*(const Matrix<P, C, K> &x) const;

    Matrix<P, R, C> &operator*=(const Matrix<P, C, C> &x);

    Matrix<P, R, C> operator+(const P &x) const;

    Matrix<P, R, C> &operator+=(const P &x);

    Matrix<P, R, C> operator+(const Matrix<P, R, C> &x) const;

    Matrix<P, R, C> &operator+=(const Matrix<P, R, C> &x);

    Matrix<P, R, C> operator-(const P &x) const;

    Matrix<P, R, C> &operator-=(const P &x);

    Matrix<P, R, C> operator-(const Matrix<P, R, C> &x) const;

    Matrix<P, R, C> &operator-=(const Matrix<P, R, C> &x);

    Matrix<P, R, C> &operator=(const Matrix<P, R, C> &x);

    bool operator==(const Matrix<P, R, C> &x) const;

    template<typename Z, size_t M, size_t N>
    friend bool nearEqual(const Matrix<Z, M, N> &left, const Matrix<Z, M, N> &right, Z epsilon);

    Matrix<P, C, R> T() const;

    explicit Matrix(const std::shared_ptr<P[R * C]> &_data);

    void make_transpose();

private:
    [[nodiscard]] std::string print() const;

    bool isTranspose{false};

    std::shared_ptr<std::array<std::array<P, C>, R>> data;
};

#include "operators.tpp"
#include "utilities.tpp"
#include "Matrix.tpp"

#endif //MATLIBCPP_MATRIX_H
