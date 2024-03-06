//
// Created by Theo Lincke on 1/25/24.
//

template<typename T, std::size_t M, std::size_t N, std::size_t K>
Matrix<T, M, K> matMul(const Matrix<T, M, N> &left, const Matrix<T, N, K> &right) {
    Matrix<T, M, K> ret{};
    for (std::size_t rowL = 0; rowL < M; ++rowL) {
        for (std::size_t colR = 0; colR < K; ++colR) {
            T sum = left[rowL][0] * right[0][colR];
            for (std::size_t colL = 1; colL < N; ++colL) {
                sum += left[rowL][colL] * right[colL][colR];
            }
            ret[rowL][colR] = sum;
        }
    }
    return ret;
}

template<typename T, std::size_t R, std::size_t C>
void scalMul_inline(Matrix<T, R, C> &left, const T &right) {
    for (std::size_t row = 0; row < R; ++row) {
        for (std::size_t col = 0; col < C; ++col) {
            left[row][col] *= right;
        }
    }
}

template<typename T, size_t R, size_t C>
void matAdd_inline(Matrix<T, R, C> &left, const Matrix<T, R, C> &right) {
    for (std::size_t row = 0; row < R; ++row) {
        for (std::size_t col = 0; col < C; ++col) {
            left[row][col] += right[row][col];
        }
    }
}

template<typename T, size_t R, size_t C>
void scalAdd_inline(Matrix<T, R, C> &left, const T &right) {
    for (std::size_t row = 0; row < R; ++row) {
        for (std::size_t col = 0; col < C; ++col) {
            left[row][col] += right;
        }
    }
}

template<typename T, size_t R, size_t C>
void matSub_inline(Matrix<T, R, C> &left, const Matrix<T, R, C> &right) {
    for (std::size_t row = 0; row < R; ++row) {
        for (std::size_t col = 0; col < C; ++col) {
            left[row][col] -= right[row][col];
        }
    }
}

template<typename T, size_t R, size_t C>
void scalSub_inline(Matrix<T, R, C> &left, const T &right) {
    for (std::size_t row = 0; row < R; ++row) {
        for (std::size_t col = 0; col < C; ++col) {
            left[row][col] -= right;
        }
    }
}

template<typename Z, size_t M, size_t N>
bool nearEqual(const Matrix<Z, M, N> &left, const Matrix<Z, M, N> &right, Z epsilon) {
    for (int row = 0; row < M; ++row) {
        for (int col = 0; col < N; ++col) {
            if (std::abs(left[row][col] - right[row][col]) > epsilon) {
                return false;
            }
        }
    }
    return true;
}

