//
// Created by Theo Lincke on 1/25/24.
//

#ifndef MATLIBCPP_ALGORITHMS_H
#define MATLIBCPP_ALGORITHMS_H

#include "Matrix.h"

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

#endif //MATLIBCPP_ALGORITHMS_H
