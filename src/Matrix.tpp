//
// Created by Theo Lincke on 3/3/24.
//

namespace mcpp {
    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C>::Matrix() {
        data_init();

        std::memset(data.get(), 0, sizeof(P) * R * C);
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C>::Matrix(const Matrix<P, R, C> &rhs) {
        data_init();

        std::memcpy(data.get(), rhs.data.get(), sizeof(P) * R * C);
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C>::Matrix(const std::initializer_list<std::initializer_list<P>> &_data) {
        data_init();
        if (_data.size() != R) {
            std::stringstream ss;
            ss << "Invalid constructor for Matrix with row size " << R;
            ss << " Got initializer list of row size: " << _data.size();
            throw std::invalid_argument(ss.str());
        }

        int ri = 0;
        int ci = 0;
        for (auto row: _data) {
            if (row.size() != C) {
                std::stringstream ss;
                ss << "Invalid constructor for Matrix with col size " << C;
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
    Matrix<P, R, C>::Matrix(std::shared_ptr<std::array<P, C * R>> &_data) {
        data = _data;
    }

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, C, R> Matrix<P, R, C>::T() {
        Matrix<P, C, R> ret = Matrix<P, C, R>(data);
        ret.make_transpose();
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    void Matrix<P, R, C>::make_transpose() {
        isTranspose = !isTranspose;
    }

    template<typename P, std::size_t R, std::size_t C>
    void Matrix<P, R, C>::data_init() {
        data = std::shared_ptr<std::array<P, C * R>>(new std::array<P, C * R>);
    }

    template<typename P, std::size_t R, std::size_t C>
    std::string Matrix<P, R, C>::print() const {
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

    template<typename P, std::size_t R, std::size_t C>
    Matrix<P, R, C>::Slice::Slice(int _index, bool _isCol, std::shared_ptr<std::array<P, C * R>> _data) {
        index = _index;
        isCol = _isCol;
        data = _data;
    }

}

