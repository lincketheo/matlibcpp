//
// Created by Theo Lincke on 1/25/24.
//

namespace mcpp {
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

    template<typename P, size_t R, size_t C>
    P pNorm(const Matrix<P, R, C> &m, double p) {
        P ret = 0;
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                ret += std::pow(m[row][col], p);
            }
        }
        return std::pow(ret, 1 / p);
    }

    template<typename P, size_t R, size_t C>
    void normalize_inline(Matrix<P, R, C> &m, double p) {
        P norm = pNorm(m, p);
        m *= 1/norm;
    }

    template<typename P, size_t R, size_t C>
    bool hasNan(const Matrix<P, R, C> &m) {
        for (std::size_t _row = 0; _row < R; ++_row) {
            for (std::size_t _col = 0; _col < C; ++_col) {
                if (std::isnan(m[_row][_col])) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename P, size_t R, size_t C>
    bool hasInf(const Matrix<P, R, C> &m) {
        for (std::size_t _row = 0; _row < R; ++_row) {
            for (std::size_t _col = 0; _col < C; ++_col) {
                if (std::isinf(m[_row][_col])) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename P, size_t R, size_t C>
    void argMax(const Matrix<P, R, C> &m, std::size_t &row, std::size_t &col) {
        row = 0;
        col = 0;
        for (std::size_t _row = 0; _row < R; ++_row) {
            for (std::size_t _col = 0; _col < C; ++_col) {
                if (m[_row][_col] > m[row][col]) {
                    row = _row;
                    col = _col;
                }
            }
        }
    }

    template<typename P, size_t R, size_t C>
    P max(const Matrix<P, R, C> &m) {
        P ret = m[0][0];

        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                if (m[row][col] > ret) {
                    ret = m[row][col];
                }
            }
        }

        return ret;
    }

    template<typename P, size_t R, size_t C>
    void argMin(const Matrix<P, R, C> &m, std::size_t &row, std::size_t &col) {
        row = 0;
        col = 0;
        for (std::size_t _row = 0; _row < R; ++_row) {
            for (std::size_t _col = 0; _col < C; ++_col) {
                if (m[_row][_col] < m[row][col]) {
                    row = _row;
                    col = _col;
                }
            }
        }
    }

    template<typename P, size_t R, size_t C>
    P min(const Matrix<P, R, C> &m) {
        P ret = m[0][0];

        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                if (m[row][col] < ret) {
                    ret = m[row][col];
                }
            }
        }

        return ret;
    }
}

