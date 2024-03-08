//
// Created by Pheo Lincke on 1/25/24.
//

#include <cstring>
#include "algorithms.h"

namespace mcpp {
    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> &Matrix<P, R, C>::operator*=(const P &x) {
        scalMul_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> Matrix<P, R, C>::operator*(const P &x) const {
        auto ret = *this;
        scalMul_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    template<std::size_t K>
    Matrix<P, R, K> Matrix<P, R, C>::operator*(const Matrix<P, C, K> &x) const {
        return matMul(*this, x);
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> &Matrix<P, R, C>::operator*=(const Matrix<P, C, C> &x) {
        *this = matMul(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> Matrix<P, R, C>::operator+(const P &x) const {
        auto ret = *this;
        scalAdd_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> &Matrix<P, R, C>::operator+=(const P &x) {
        scalAdd_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> Matrix<P, R, C>::operator+(const Matrix<P, R, C> &x) const {
        auto ret = *this;
        matAdd_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> &Matrix<P, R, C>::operator+=(const Matrix<P, R, C> &x) {
        matAdd_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> Matrix<P, R, C>::operator-(const Matrix<P, R, C> &x) const {
        auto ret = *this;
        matSub_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> &Matrix<P, R, C>::operator-=(const Matrix<P, R, C> &x) {
        matSub_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> Matrix<P, R, C>::operator-(const P &x) const {
        auto ret = *this;
        scalSub_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> &Matrix<P, R, C>::operator-=(const P &x) {
        scalSub_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C> &Matrix<P, R, C>::operator=(const Matrix<P, R, C> &x) {
        std::memcpy(this->data.get(), x.data.get(), C * R * sizeof(P));
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    bool Matrix<P, R, C>::operator==(const Matrix<P, R, C> &x) const {
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                if ((*this)[row][col] != x[row][col]) {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename P, std::size_t R, std::size_t C>
    bool Matrix<P, R, C>::operator!=(const Matrix<P, R, C> &x) const {
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                if ((*this)[row][col] != x[row][col]) {
                    return true;
                }
            }
        }
        return false;
    }
}

