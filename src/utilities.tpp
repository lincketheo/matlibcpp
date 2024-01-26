//
// Created by Theo Lincke on 1/25/24.
//

template<typename T, std::size_t R, std::size_t C>
std::string Matrix<T, R, C>::print() const {
    std::stringstream ss;
    for (int r = 0; r < R; ++r) {
        if (r == 0) {
            ss << "[[";
        } else {
            ss << " [";
        }
        for (int c = 0; c < C; ++c) {
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

