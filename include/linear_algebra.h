//
// Created by tjl on 3/19/24.
//

#ifndef MATLIBCPP_LINEAR_ALGEBRA_H
#define MATLIBCPP_LINEAR_ALGEBRA_H

#include <Matrix.h>

namespace mcpp {
    template<typename P, size_t R, size_t C>
    Matrix<P, R, C> ident();

    template<typename Z, size_t M, size_t N>
    bool nearEqual(const Matrix<Z, M, N> &left, const Matrix<Z, M, N> &right, Z epsilon);

    template<typename P, size_t M, size_t N, size_t K>
    Matrix<P, M, K> matMul(const Matrix<P, M, N> &left, const Matrix<P, N, K> &right);

    template<typename P, size_t R, size_t C>
    void scalMul_inline(Matrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    void matAdd_inline(Matrix<P, R, C> &left, const Matrix<P, R, C> &right);

    template<typename P, size_t R, size_t C>
    void scalAdd_inline(Matrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    void matSub_inline(Matrix<P, R, C> &left, const Matrix<P, R, C> &right);

    template<typename P, size_t R, size_t C>
    void scalSub_inline(Matrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    P pNorm(const Matrix<P, R, C> &m, P p);

    template<typename P, size_t R, size_t C>
    void normalize_inline(Matrix<P, R, C> &m, P p);

    template<typename P, size_t R, size_t C>
    bool hasNan(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    bool hasInf(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void argMax(const Matrix<P, R, C> &m, std::size_t &row, std::size_t &col);

    template<typename P, size_t R, size_t C>
    P max(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void argMin(const Matrix<P, R, C> &m, std::size_t &row, std::size_t &col);

    template<typename P, size_t R, size_t C>
    P min(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    P trace(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void rotate_inline(Matrix<P, R, C> &m, std::size_t x, std::size_t y, double theta);

    template<typename P, size_t R, size_t C>
    void gaussJordan_inline(Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void gaussJordanRREF_inline(Matrix<P, R, C> &m);
}

#include "../src/linear_algebra.tpp"

#endif //MATLIBCPP_LINEAR_ALGEBRA_H
