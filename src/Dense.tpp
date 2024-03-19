//
// Created by tjl on 3/19/24.
//

namespace mcpp {
    template<typename P, std::size_t BATCH, std::size_t IN, std::size_t OUT>
    std::array<Matrix<P, OUT, 1>, BATCH> Dense<P, BATCH, IN, OUT>::evaluate(
            const std::array<Matrix<P, IN, 1>, BATCH> &inputs) {

        std::array<Matrix<P, OUT, 1>, BATCH> outputs;

        for (int i = 0; i < inputs.size(); ++i) {
            outputs[i] = weights * inputs[i] + biases;
        }

        return outputs;
    }
}