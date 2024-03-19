//
// Created by tjl on 3/19/24.
//

namespace mcpp {
    ////////////////////////// Algorithms
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


    template<typename P, size_t R, size_t C>
    P pNorm(const Matrix<P, R, C> &m, P p) {
        P ret = 0;
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                ret += std::pow(m[row][col], p);
            }
        }
        return std::pow(ret, 1 / p);
    }

    template<typename P, size_t R, size_t C>
    void normalize_inline(Matrix<P, R, C> &m, P p) {
        P norm = pNorm(m, p);
        m *= 1 / norm;
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

    template<typename P, size_t R, size_t C>
    P trace(const Matrix<P, R, C> &m) {
        P ret = m[0][0];
        std::size_t i = 1;
        while (i < C && i < R) {
            ret += m[i][i];
            i++;
        }

        return ret;
    }

    template<typename P, size_t R, size_t C>
    void rotate_inline(Matrix<P, R, C> &m, std::size_t x, std::size_t y, double theta) {
        auto rot = ident<P, R, R>();
        rot[x][x] = std::cos(theta);
        rot[y][x] = std::sin(theta);
        rot[y][y] = std::cos(theta);
        rot[x][y] = -std::sin(theta);
        m = rot * m;
    }

    template<typename P, size_t R, size_t C>
    void gaussJordan_inline(Matrix<P, R, C> &m) {
        int i = 0;
        int j = 0;
        while (i < R && j < C) {
            int s = 1;

            // Ensure the first pivot is not 0
            while (m[i][j] == 0 && i + s < R - 1) {
                // swap rows i and s
                auto temp = m[i];
                m[i] = m[s];
                m[s] = temp;
            }

            //
            if (m[i][j] != 0) {
                m[i] *= 1 / m[i][j];
                for (int x = 1; i + x < R; ++x) {
                    if (m[i + x][j] != 0) {
                        m[x + i] -= (m[i] * m[i + x][j]);
                    }
                }
            }
            i++;
            j++;
        }
    }

    template<typename P, size_t R, size_t C>
    void gaussJordanRREF_inline(Matrix<P, R, C> &m) {
        gaussJordan_inline(m);
        int i = std::min(R, C) - 1;
        int j = i;
        while (i >= 0) {
            if (m[i][j] != 0) {
                for (int x = 1; i - x >= 0; ++x) {
                    m[i - x] = m[i - x] - (m[i] * m[i - x][j]);
                }
            }
            i--;
            j--;
        }
    }

    ////////////////////////// Operators
    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C> Matrix<P, R, C>::operator[](int i) {
        int ii = i;
        if (ii < 0) {
            ii += R;
        }
        if (ii >= R) {
            std::stringstream ss;
            ss << "Invalid row index: " << i << " for matrix with " << R << " rows";
            throw std::invalid_argument(ss.str());
        }
        if (isTranspose) {
            return MatrixSlice<P, R, C>(ii, true, data);
        } else {
            return MatrixSlice<P, R, C>(ii, false, data);
        }
    }

    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C> Matrix<P, R, C>::operator[](int i) const {
        int ii = i;
        if (ii < 0) {
            ii += R;
        }
        if (ii >= R) {
            std::stringstream ss;
            ss << "Invalid row index: " << i << " for matrix with " << R << " rows";
            throw std::invalid_argument(ss.str());
        }
        if (isTranspose) {
            return MatrixSlice<P, R, C>(ii, true, data);
        } else {
            return MatrixSlice<P, R, C>(ii, false, data);
        }
    }

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

    template<typename P, size_t R, size_t C>
    Matrix<P, R, C> ident() {
        Matrix<P, R, C> ret;
        for (std::size_t i = 0; i < R && i < C; ++i) {
            ret[i][i] = 1;
        }
        return ret;
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

}
