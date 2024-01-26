//
// Created by Theo Lincke on 1/25/24.
//

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> &Matrix<T, R, C>::operator*=(const T &x) {
    scalMul_inline(*this, x);
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator*(const T &x) const {
    auto ret = *this;
    scalMul_inline(ret, x);
    return ret;
}

template<typename T, std::size_t R, std::size_t C>
template<std::size_t K>
Matrix<T, R, K> Matrix<T, R, C>::operator*(const Matrix<T, C, K> &x) const {
    return matMul(*this, x);
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> &Matrix<T, R, C>::operator*=(const Matrix<T, C, C> &x) {
    *this = matMul(*this, x);
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator+(const T &x) const {
    auto ret = *this;
    scalAdd_inline(ret, x);
    return ret;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> &Matrix<T, R, C>::operator+=(const T &x) {
    scalAdd_inline(*this, x);
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator+(const Matrix<T, R, C> &x) const {
    auto ret = *this;
    matAdd_inline(ret, x);
    return ret;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> &Matrix<T, R, C>::operator+=(const Matrix<T, R, C> &x) {
    matAdd_inline(*this, x);
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator-(const Matrix<T, R, C> &x) const {
    auto ret = *this;
    matSub_inline(ret, x);
    return ret;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> &Matrix<T, R, C>::operator-=(const Matrix<T, R, C> &x) {
    matSub_inline(*this, x);
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator-(const T &x) const {
    auto ret = *this;
    scalSub_inline(ret, x);
    return ret;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> &Matrix<T, R, C>::operator-=(const T &x) {
    scalSub_inline(*this, x);
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C> &Matrix<T, R, C>::operator=(const Matrix<T, R, C> &x) {
    this->data = x.data;
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
bool Matrix<T, R, C>::operator==(const Matrix<T, R, C> &x) const {
    for (int row = 0; row < R; ++row) {
        for (int col = 0; col < C; ++col) {
            if (this->data[row][col] != x.data[row][col]) {
                return false;
            }
        }
    }
    return true;
}

