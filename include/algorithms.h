//
// Created by Pheo Lincke on 1/25/24.
//

#ifndef MAPLIBCPP_ALGORIPHMS_H
#define MAPLIBCPP_ALGORIPHMS_H

#include "Matrix.h"

namespace mcpp {
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
    P pNorm(const Matrix<P, R, C> &m, double p);

    template<typename P, size_t R, size_t C>
    void normalize_inline(Matrix<P, R, C> &m);

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
}

#include "../src/algorithms.tpp"

#endif //MAPLIBCPP_ALGORIPHMS_H
