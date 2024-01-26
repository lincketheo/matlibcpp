//
// Created by Theo Lincke on 1/25/24.
//
#include <gtest/gtest.h>
#include "Matrix.h"

TEST(Matrix, Equ) {
    std::array<std::array<double, 3>, 2> a{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};
    std::array<std::array<double, 3>, 2> b{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};
    std::array<std::array<double, 3>, 2> c{{{3.1, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};
    std::array<std::array<double, 3>, 2> d{{{3.300000001, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};

    Matrix<double, 2, 3> aM{a};
    Matrix<double, 2, 3> bM{b};
    Matrix<double, 2, 3> cM{c};
    Matrix<double, 2, 3> dM{d};

    ASSERT_EQ(aM, aM);
    ASSERT_EQ(aM, bM);
    ASSERT_NE(aM, cM);
    ASSERT_NE(aM, dM);
    ASSERT_TRUE(nearEqual(aM, dM, 0.0001));
}

TEST(Matrix, MatMul) {
    std::array<std::array<double, 3>, 2> a{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};

    std::array<std::array<double, 2>, 3> b{{{3.0, 4.1},
                                            {1.5, 2.2},
                                            {3.4, 4.3}}};

    std::array<std::array<double, 3>, 3> c{{{3.0, 4.5, 6.0},
                                            {1.0, 2.9, 7.1},
                                            {1.1, -0.9, 9.1}}};

    std::array<std::array<double, 2>, 2> exp1{{{37.05, 49.23},
                                               {31.49, 41.01}}};

    std::array<std::array<double, 3>, 2> exp2{{{21.0, 22.5, 106.35},
                                               {13.71, 6.52, 91.2}}};

    Matrix<double, 2, 3> aM{a};
    Matrix<double, 3, 2> bM{b};
    Matrix<double, 3, 3> cM{c};

    Matrix<double, 2, 2> expected1{exp1};
    Matrix<double, 2, 3> expected2{exp2};

    EXPECT_EQ(aM * bM, expected1);

    aM *= cM;
    std::cout << aM << std::endl;
    EXPECT_TRUE(nearEqual(aM, expected2, 0.0001));
}

TEST(Matrix, ScalMul) {
    std::array<std::array<double, 3>, 2> a{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};

    std::array<std::array<double, 3>, 2> exp{{{14.85, 20.25, 27.0},
                                              {4.5, 13.05, 31.95}}};

    Matrix<double, 2, 3> aM{a};
    Matrix<double, 2, 3> expected{exp};

    EXPECT_TRUE(nearEqual(aM * 4.5, expected, 0.0001));
    aM *= 4.5;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(Matrix, MatAdd) {
    std::array<std::array<double, 3>, 2> a{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};

    std::array<std::array<double, 3>, 2> b{{{4.1, 8.1, 1.0},
                                            {4.5, 1.05, 3.95}}};

    std::array<std::array<double, 3>, 2> exp{{{7.4, 12.6, 7.0},
                                              {5.5, 3.95, 11.05}}};

    Matrix<double, 2, 3> aM{a};
    Matrix<double, 2, 3> bM{b};
    Matrix<double, 2, 3> expected{exp};

    EXPECT_TRUE(nearEqual(aM + bM, expected, 0.0001));
    aM += bM;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(Matrix, ScalAdd) {
    std::array<std::array<double, 3>, 2> a{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};

    std::array<std::array<double, 3>, 2> exp{{{4.64, 5.84, 7.34},
                                              {2.34, 4.24, 8.44}}};

    Matrix<double, 2, 3> aM{a};
    Matrix<double, 2, 3> expected{exp};

    EXPECT_TRUE(nearEqual(aM + 1.34, expected, 0.0001));
    aM += 1.34;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(Matrix, MatSub) {
    std::array<std::array<double, 3>, 2> a{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};

    std::array<std::array<double, 3>, 2> b{{{4.1, 8.1, 1.0},
                                            {4.5, 1.05, 3.95}}};

    std::array<std::array<double, 3>, 2> exp{{{-0.8, -3.6, 5.0},
                                              {-3.5, 1.85, 3.15}}};

    Matrix<double, 2, 3> aM{a};
    Matrix<double, 2, 3> bM{b};
    Matrix<double, 2, 3> expected{exp};

    EXPECT_TRUE(nearEqual(aM - bM, expected, 0.0001));
    aM -= bM;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(Matrix, ScalSub) {
    std::array<std::array<double, 3>, 2> a{{{3.3, 4.5, 6.0},
                                            {1.0, 2.9, 7.1}}};

    std::array<std::array<double, 3>, 2> exp{{{1.96, 3.16, 4.66},
                                              {-0.34, 1.56, 5.76}}};

    Matrix<double, 2, 3> aM{a};
    Matrix<double, 2, 3> expected{exp};

    EXPECT_TRUE(nearEqual(aM - 1.34, expected, 0.0001));
    aM -= 1.34;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(Matrix, MatCopy) {
    EXPECT_EQ(5, 5);
}
