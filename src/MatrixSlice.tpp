
#include <MatrixSlice.h>
#include <sstream>

namespace mcpp {
    ////////////////////////// MatrixSlice
    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C>::MatrixSlice(int _index, bool _isCol,
                                                    std::shared_ptr<std::array<P, C * R>> _data) {
        index = _index;
        isCol = _isCol;
        data = _data;
    }

    template<typename P, std::size_t R, std::size_t C>
    P &MatrixSlice<P, R, C>::operator[](int i) {
        int ii = i;
        if (ii < 0) {
            ii += C;
        }
        if (ii >= C) {
            std::stringstream ss;
            ss << "Invalid col index: " << i << " for matrix with " << C << " cols";
            throw std::invalid_argument(ss.str());
        }
        if (isCol) {
            return (*data)[R * ii + index];
        } else {
            return (*data)[index * C + ii];
        }
    }

    template<typename P, std::size_t R, std::size_t C>
    P MatrixSlice<P, R, C>::operator[](int i) const {
        int ii = i;
        if (ii < 0) {
            ii += C;
        }
        if (ii >= C) {
            std::stringstream ss;
            ss << "Invalid col index: " << i << " for matrix with " << C << " cols";
            throw std::invalid_argument(ss.str());
        }
        if (isCol) {
            return (*data)[R * ii + index];
        } else {
            return (*data)[index * C + ii];
        }
    }

    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C> &MatrixSlice<P, R, C>::operator*=(P f) {
        for (int i = 0; i < C; ++i) {
            (*this)[i] *= f;
        }
        return (*this);
    }

    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C> &MatrixSlice<P, R, C>::operator=(
            const MatrixSlice &right
    ) {
        for (int i = 0; i < C; ++i) {
            (*this)[i] = right[i];
        }
        return *this;
    }

    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C> MatrixSlice<P, R, C>::operator*(P f) {
        MatrixSlice ret = *this;
        ret *= f;
        return ret;
    }

    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C> &MatrixSlice<P, R, C>::operator-=(
            const MatrixSlice &right
    ) {
        for (int i = 0; i < C; ++i) {
            (*this)[i] -= right[i];
        }
        return (*this);
    }

    template<typename P, std::size_t R, std::size_t C>
    MatrixSlice<P, R, C> MatrixSlice<P, R, C>::operator-(
            const MatrixSlice &right
    ) {
        MatrixSlice ret = *this;
        ret -= right;
        return ret;
    }
}