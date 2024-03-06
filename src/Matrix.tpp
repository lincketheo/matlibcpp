//
// Created by Theo Lincke on 3/3/24.
//

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
Matrix<P, R, C>::Matrix(const std::array<std::array<P, C>, R> &_data) {
    data_init();

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            (*this)[i][j] = _data[i][j];
        }
    }
}

template<typename P, std::size_t R, std::size_t C>
Matrix<P, R, C>::Matrix(const std::shared_ptr<P[R * C]> &_data) {
    data = _data;
}

template<typename P, std::size_t R, std::size_t C>
Matrix<P, C, R> Matrix<P, R, C>::T() const {
    auto ret = Matrix<P, C, R>{data};
    ret.make_transpose();
    return ret;
}

template<typename P, std::size_t R, std::size_t C>
void Matrix<P, R, C>::make_transpose() {
    isTranspose = !isTranspose;
}

template<typename P, std::size_t R, std::size_t C>
void Matrix<P, R, C>::data_init() {
    data = std::make_shared<std::valarray<P>>(std::valarray<P>{R * C});
}
