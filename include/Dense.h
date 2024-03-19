//
// Created by tjl on 3/13/24.
//

#ifndef MATLIBCPP_DENSE_H
#define MATLIBCPP_DENSE_H

#include <cstdlib>
#include <Matrix.h>

namespace mcpp {
    template<typename P, std::size_t BATCH, std::size_t IN, std::size_t OUT>
    class Dense {

        std::array<Matrix<P, OUT, 1>, BATCH> evaluate(
                const std::array<Matrix<P, IN, 1>, BATCH>& inputs
        );

    private:
        std::array<Matrix<P, IN, 1>, BATCH> inputs;

        Matrix<P, OUT, IN> weights;
        Matrix<P, OUT, 1> biases;

        Matrix<P, OUT, IN> weights_updates;
        Matrix<P, OUT, 1> biases_updates;
    };
}

#include "../src/Dense.tpp"

#endif //MATLIBCPP_DENSE_H
