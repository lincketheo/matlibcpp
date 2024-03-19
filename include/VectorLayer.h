//
// Created by tjl on 3/14/24.
//

#ifndef MATLIBCPP_VECTORLAYER_H
#define MATLIBCPP_VECTORLAYER_H

#include <Matrix.h>

namespace mcpp {
    template<typename P, std::size_t IN, std::size_t OUT>
    class VectorLayer {
    public:
        Matrix<P, OUT, 1> consume(const Matrix<P, IN, 1>);
    };
}

#endif //MATLIBCPP_VECTORLAYER_H
