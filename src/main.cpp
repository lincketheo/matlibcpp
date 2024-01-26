//
// Created by Theo Lincke on 1/20/24.
//

#include <iostream>
#include "Matrix.h"

int main() {

    std::array<std::array<double, 3>, 2> a{{{3.0, 4.0, 6.0},
                                            {1.0, 2.0, 7.0}}};

    std::array<std::array<double, 3>, 2> c{{{3.0, 4.0, 6.0},
                                            {1.0, 2.0, 7.0}}};

    std::array<std::array<double, 2>, 3> b{{{3.0, 4.0},
                                            {1.0, 2.0},
                                            {3.0, 4.0}}};

    Matrix<double, 2, 3> aM{a};

    Matrix<double, 2, 3> cM{c};

    Matrix<double, 3, 2> bM{b};

    std::cout << aM << std::endl;
    auto kM = aM * bM;
    std::cout << kM << std::endl;
    aM *= 3.0;
    std::cout << aM << std::endl;
    aM += 5.0;
    std::cout << aM << std::endl;
    aM += cM;
    std::cout << aM << std::endl;
    aM -= 4.0;
    std::cout << aM << std::endl;
    aM -= cM;
    std::cout << aM << std::endl;

    return 0;
}
