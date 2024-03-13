//
// Created by Theo Lincke on 1/25/24.
//

#include <cstring>

namespace mcpp {
    ////////////////////////// Algorithms
    template<typename T, std::size_t M, std::size_t N, std::size_t K>
    GenericMatrix<T, M, K> matMul(const GenericMatrix<T, M, N> &left, const GenericMatrix<T, N, K> &right) {
        GenericMatrix<T, M, K> ret{};
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
    void scalMul_inline(GenericMatrix<T, R, C> &left, const T &right) {
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                left[row][col] *= right;
            }
        }
    }

    template<typename T, size_t R, size_t C>
    void matAdd_inline(GenericMatrix<T, R, C> &left, const GenericMatrix<T, R, C> &right) {
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                left[row][col] += right[row][col];
            }
        }
    }

    template<typename T, size_t R, size_t C>
    void scalAdd_inline(GenericMatrix<T, R, C> &left, const T &right) {
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                left[row][col] += right;
            }
        }
    }

    template<typename T, size_t R, size_t C>
    void matSub_inline(GenericMatrix<T, R, C> &left, const GenericMatrix<T, R, C> &right) {
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                left[row][col] -= right[row][col];
            }
        }
    }

    template<typename T, size_t R, size_t C>
    void scalSub_inline(GenericMatrix<T, R, C> &left, const T &right) {
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                left[row][col] -= right;
            }
        }
    }


    template<typename P, size_t R, size_t C>
    P pNorm(const GenericMatrix<P, R, C> &m, P p) {
        P ret = 0;
        for (std::size_t row = 0; row < R; ++row) {
            for (std::size_t col = 0; col < C; ++col) {
                ret += std::pow(m[row][col], p);
            }
        }
        return std::pow(ret, 1 / p);
    }

    template<typename P, size_t R, size_t C>
    void normalize_inline(GenericMatrix<P, R, C> &m, P p) {
        P norm = pNorm(m, p);
        m *= 1 / norm;
    }

    template<typename P, size_t R, size_t C>
    bool hasNan(const GenericMatrix<P, R, C> &m) {
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
    bool hasInf(const GenericMatrix<P, R, C> &m) {
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
    void argMax(const GenericMatrix<P, R, C> &m, std::size_t &row, std::size_t &col) {
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
    P max(const GenericMatrix<P, R, C> &m) {
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
    void argMin(const GenericMatrix<P, R, C> &m, std::size_t &row, std::size_t &col) {
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
    P min(const GenericMatrix<P, R, C> &m) {
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
    P trace(const GenericMatrix<P, R, C> &m) {
        P ret = m[0][0];
        std::size_t i = 1;
        while (i < C && i < R) {
            ret += m[i][i];
            i++;
        }

        return ret;
    }

    template<typename P, size_t R, size_t C>
    void rotate_inline(GenericMatrix<P, R, C> &m, std::size_t x, std::size_t y, double theta) {
        auto rot = ident<P, R, R>();
        rot[x][x] = std::cos(theta);
        rot[y][x] = std::sin(theta);
        rot[y][y] = std::cos(theta);
        rot[x][y] = -std::sin(theta);
        m = rot * m;
    }

    template<typename P, size_t R, size_t C>
    void gaussJordan_inline(GenericMatrix<P, R, C> &m) {
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
    void gaussJordanRREF_inline(GenericMatrix<P, R, C> &m) {
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
    GenericMatrixSlice<P, R, C> GenericMatrix<P, R, C>::operator[](int i) {
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
            return GenericMatrixSlice<P, R, C>(ii, true, data);
        } else {
            return GenericMatrixSlice<P, R, C>(ii, false, data);
        }
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrixSlice<P, R, C> GenericMatrix<P, R, C>::operator[](int i) const {
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
            return GenericMatrixSlice<P, R, C>(ii, true, data);
        } else {
            return GenericMatrixSlice<P, R, C>(ii, false, data);
        }
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> &GenericMatrix<P, R, C>::operator*=(const P &x) {
        scalMul_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> GenericMatrix<P, R, C>::operator*(const P &x) const {
        auto ret = *this;
        scalMul_inline(ret, x);
        return ret;
    }

    template<typename P, size_t R, size_t C>
    GenericMatrix<P, R, C> ident() {
        GenericMatrix<P, R, C> ret;
        for (std::size_t i = 0; i < R && i < C; ++i) {
            ret[i][i] = 1;
        }
        return ret;
    }

    template<typename Z, size_t M, size_t N>
    bool nearEqual(const GenericMatrix<Z, M, N> &left, const GenericMatrix<Z, M, N> &right, Z epsilon) {
        for (int row = 0; row < M; ++row) {
            for (int col = 0; col < N; ++col) {
                if (std::abs(left[row][col] - right[row][col]) > epsilon) {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename P, std::size_t R, std::size_t C>
    template<std::size_t K>
    GenericMatrix<P, R, K> GenericMatrix<P, R, C>::operator*(const GenericMatrix<P, C, K> &x) const {
        return matMul(*this, x);
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> &GenericMatrix<P, R, C>::operator*=(const GenericMatrix<P, C, C> &x) {
        *this = matMul(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> GenericMatrix<P, R, C>::operator+(const P &x) const {
        auto ret = *this;
        scalAdd_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> &GenericMatrix<P, R, C>::operator+=(const P &x) {
        scalAdd_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> GenericMatrix<P, R, C>::operator+(const GenericMatrix<P, R, C> &x) const {
        auto ret = *this;
        matAdd_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> &GenericMatrix<P, R, C>::operator+=(const GenericMatrix<P, R, C> &x) {
        matAdd_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> GenericMatrix<P, R, C>::operator-(const GenericMatrix<P, R, C> &x) const {
        auto ret = *this;
        matSub_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> &GenericMatrix<P, R, C>::operator-=(const GenericMatrix<P, R, C> &x) {
        matSub_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> GenericMatrix<P, R, C>::operator-(const P &x) const {
        auto ret = *this;
        scalSub_inline(ret, x);
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> &GenericMatrix<P, R, C>::operator-=(const P &x) {
        scalSub_inline(*this, x);
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C> &GenericMatrix<P, R, C>::operator=(const GenericMatrix<P, R, C> &x) {
        std::memcpy(this->data.get(), x.data.get(), C * R * sizeof(P));
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    bool GenericMatrix<P, R, C>::operator==(const GenericMatrix<P, R, C> &x) const {
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
    bool GenericMatrix<P, R, C>::operator!=(const GenericMatrix<P, R, C> &x) const {
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                if ((*this)[row][col] != x[row][col]) {
                    return true;
                }
            }
        }
        return false;
    }

    ////////////////////////// Constructors
    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C>::GenericMatrix() {
        data_init();

        std::memset(data.get(), 0, sizeof(P) * R * C);
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C>::GenericMatrix(const GenericMatrix<P, R, C> &rhs) {
        data_init();

        std::memcpy(data.get(), rhs.data.get(), sizeof(P) * R * C);
    }

    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C>::GenericMatrix(const std::initializer_list<std::initializer_list<P>> &_data) {
        data_init();
        if (_data.size() != R) {
            std::stringstream ss;
            ss << "Invalid constructor for GenericMatrix with row size " << R;
            ss << " Got initializer list of row size: " << _data.size();
            throw std::invalid_argument(ss.str());
        }

        int ri = 0;
        int ci = 0;
        for (auto row: _data) {
            if (row.size() != C) {
                std::stringstream ss;
                ss << "Invalid constructor for GenericMatrix with col size " << C;
                ss << " Row: " << ri << " of initializer list ";
                ss << "has col size " << row.size();
                throw std::invalid_argument(ss.str());
            }
            for (auto elem: row) {
                (*this)[ri][ci] = elem;
                ci++;
            }
            ci = 0;
            ri++;
        }
    }


    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, R, C>::GenericMatrix(std::shared_ptr<std::array<P, C * R>> &_data) {
        data = _data;
    }

    ////////////////////////// Utils
    template<typename P, std::size_t R, std::size_t C>
    GenericMatrix<P, C, R> GenericMatrix<P, R, C>::T() {
        GenericMatrix<P, C, R> ret = GenericMatrix<P, C, R>(data);
        ret.make_transpose();
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    void GenericMatrix<P, R, C>::make_transpose() {
        isTranspose = !isTranspose;
    }

    template<typename P, std::size_t R, std::size_t C>
    void GenericMatrix<P, R, C>::data_init() {
        data = std::shared_ptr<std::array<P, C * R>>(new std::array<P, C * R>);
    }

    template<typename P, std::size_t R, std::size_t C>
    std::string GenericMatrix<P, R, C>::print() const {
        std::stringstream ss;
        for (int r = 0; r < R; ++r) {
            if (r == 0) {
                ss << "[[";
            } else {
                ss << " [";
            }
            for (int c = 0; c < C; ++c) {
                (*this)[r];
                ss << (*this)[r][c];
                if (c != C - 1) {
                    ss << ", ";
                }
            }
            ss << "]";
            if (r == R - 1) {
                ss << "]";
            } else {
                ss << "," << std::endl;
            }
        }
        return ss.str();
    }
}

