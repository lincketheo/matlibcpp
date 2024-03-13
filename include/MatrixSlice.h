//
// Created by tjl on 3/13/24.
//

#ifndef MATLIBCPP_GENERICMATRIXSLICE_H
#define MATLIBCPP_GENERICMATRIXSLICE_H

#include <memory>

namespace mcpp {
/**
 * A Wrapper around an array that indexes rows / columns
 * as if they're contiguous
 */
    template<typename P, std::size_t R, std::size_t C>
    class MatrixSlice {
    public:
        MatrixSlice() = delete;

        MatrixSlice(int _index, bool _isCol, std::shared_ptr<std::array<P, C * R>> _data);

        P &operator[](int i);

        P operator[](int i) const;

        // TODO test
        MatrixSlice &operator*=(P f);

        // TODO test
        MatrixSlice &operator=(const MatrixSlice &right);

        // TODO test
        MatrixSlice operator*(P f);

        // TODO test
        MatrixSlice &operator-=(const MatrixSlice &right);

        // TODO test
        MatrixSlice operator-(const MatrixSlice &right);

    private:
        bool isCol;
        int index;
        std::shared_ptr<std::array<P, C * R>> data;
    };
}

#include "../src/MatrixSlice.tpp"

#endif //MATLIBCPP_GENERICMATRIXSLICE_H
