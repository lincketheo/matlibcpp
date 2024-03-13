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
    class GenericMatrixSlice {
    public:
        GenericMatrixSlice() = delete;

        GenericMatrixSlice(int _index, bool _isCol, std::shared_ptr<std::array<P, C * R>> _data);

        P &operator[](int i);

        P operator[](int i) const;

        // TODO test
        GenericMatrixSlice &operator*=(P f);

        // TODO test
        GenericMatrixSlice &operator=(const GenericMatrixSlice &right);

        // TODO test
        GenericMatrixSlice operator*(P f);

        // TODO test
        GenericMatrixSlice &operator-=(const GenericMatrixSlice &right);

        // TODO test
        GenericMatrixSlice operator-(const GenericMatrixSlice &right);

    private:
        bool isCol;
        int index;
        std::shared_ptr<std::array<P, C * R>> data;
    };
}

#include "../src/GenericMatrixSlice.tpp"

#endif //MATLIBCPP_GENERICMATRIXSLICE_H
