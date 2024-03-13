//
// Created by Theo Lincke on 1/25/24.
//
#include <gtest/gtest.h>
#include "GenericMatrix.h"

using namespace mcpp;

TEST(GenericMatrix, ConstructorVal) {
    // I know there's EXPECT_THROW, but the initializer lists are
    // doing something weird, feel free to fix
    try {
        GenericMatrix<int, 2, 3> aM{{1, 2, 3}};
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid constructor for GenericMatrix with row size 2"
                               " Got initializer list of row size: 1");
    }

    try {
        GenericMatrix<int, 2, 3> aM{{1, 2, 3},
                                    {4, 5}};
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid constructor for GenericMatrix with col size 3"
                               " Row: 1 of initializer list has col size 2");
    }

    GenericMatrix<int, 2, 3> aM{{{1, 2, 3}, {4, 5, 6}}};
}

TEST(GenericMatrix, Indexing) {
    GenericMatrix<int, 2, 3> aM = {{3, 4, 6},
                                   {1, 2, 7}};

    ASSERT_EQ(aM[0][0], 3);
    ASSERT_EQ(aM[0][1], 4);
    ASSERT_EQ(aM[0][2], 6);
    ASSERT_EQ(aM[1][0], 1);
    ASSERT_EQ(aM[1][1], 2);
    ASSERT_EQ(aM[1][2], 7);

    ASSERT_EQ(aM[-1][0], 1);
    ASSERT_EQ(aM[0][-1], 6);
    ASSERT_EQ(aM[1][-2], 2);
    ASSERT_EQ(aM[-1][-3], 1);

    ASSERT_EQ(aM.T()[-1][0], 6);
    ASSERT_EQ(aM.T()[0][-1], 1);
    ASSERT_EQ(aM.T()[1][-2], 4);
    ASSERT_EQ(aM.T()[-2][-2], 4);

    try {
        aM[3][0];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid row index: 3 for matrix with 2 rows");
    }
    try {
        aM[0][3];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid col index: 3 for matrix with 3 cols");
    }
    try {
        aM[0][-4];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid col index: -4 for matrix with 3 cols");
    }
    try {
        aM[-4][0];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid row index: -4 for matrix with 2 rows");
    }

    // Transpose
    try {
        aM.T()[0][3];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid col index: 3 for matrix with 2 cols");
    }
    try {
        aM.T()[3][0];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid row index: 3 for matrix with 3 rows");
    }
    try {
        aM.T()[-4][0];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid row index: -4 for matrix with 3 rows");
    }
    try {
        aM.T()[0][-4];
        FAIL();
    } catch (std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "Invalid col index: -4 for matrix with 2 cols");
    }
}

TEST(GenericMatrix, Print) {
    GenericMatrix<int, 2, 3> aM = {{3, 4, 6},
                                   {1, 2, 7}};
    std::stringstream ss;
    ss << aM << std::endl;

    EXPECT_EQ(ss.str(), "[[3, 4, 6],\n [1, 2, 7]]\n");
}

TEST(GenericMatrix, Equ) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> bM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> cM{{3.1, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> dM{{3.30001, 4.5, 6.0},
                                   {1.0,     2.9, 7.1}};

    ASSERT_EQ(aM, aM);
    ASSERT_EQ(aM, bM);
    ASSERT_NE(aM, cM);
    ASSERT_NE(aM, dM);
    ASSERT_TRUE(nearEqual(aM, dM, 0.0001));
    ASSERT_FALSE(nearEqual(aM, dM, 0.00001));
}

TEST(GenericMatrix, MatMul) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 3, 2> bM{{3.0, 4.1},
                                   {1.5, 2.2},
                                   {3.4, 4.3}};
    GenericMatrix<double, 3, 3> cM{{3.0, 4.5,  6.0},
                                   {1.0, 2.9,  7.1},
                                   {1.1, -0.9, 9.1}};

    GenericMatrix<double, 2, 2> expected1{{37.05, 49.23},
                                          {31.49, 41.01}};
    GenericMatrix<double, 2, 3> expected2{{21.0,  22.5, 106.35},
                                          {13.71, 6.52, 91.2}};

    EXPECT_TRUE(nearEqual(aM * bM, expected1, 0.0001));

    aM *= cM;
    EXPECT_TRUE(nearEqual(aM, expected2, 0.0001));
}

TEST(GenericMatrix, ScalMul) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> expected{{14.85, 20.25, 27.0},
                                         {4.5,   13.05, 31.95}};

    EXPECT_TRUE(nearEqual(aM * 4.5, expected, 0.0001));
    aM *= 4.5;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(GenericMatrix, MatAdd) {
    GenericMatrix<double, 2, 3> aMM{{1, 2, 3},
                                    {3, 4, 5}};

    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> bM{{4.1, 8.1,  1.0},
                                   {4.5, 1.05, 3.95}};
    GenericMatrix<double, 2, 3> expected{{7.4, 12.6, 7.0},
                                         {5.5, 3.95, 11.05}};

    EXPECT_TRUE(nearEqual(aM + bM, expected, 0.0001));
    aM += bM;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(GenericMatrix, ScalAdd) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> expected{{4.64, 5.84, 7.34},
                                         {2.34, 4.24, 8.44}};

    EXPECT_TRUE(nearEqual(aM + 1.34, expected, 0.0001));
    aM += 1.34;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(GenericMatrix, MatSub) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> bM{{4.1, 8.1,  1.0},
                                   {4.5, 1.05, 3.95}};
    GenericMatrix<double, 2, 3> expected{{-0.8, -3.6, 5.0},
                                         {-3.5, 1.85, 3.15}};

    EXPECT_TRUE(nearEqual(aM - bM, expected, 0.0001));
    aM -= bM;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(GenericMatrix, ScalSub) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> expected{{1.96,  3.16, 4.66},
                                         {-0.34, 1.56, 5.76}};

    EXPECT_TRUE(nearEqual(aM - 1.34, expected, 0.0001));
    aM -= 1.34;
    EXPECT_TRUE(nearEqual(aM, expected, 0.0001));
}

TEST(GenericMatrix, MatCopy) {
    GenericMatrix<double, 2, 3> aM{{1.96,  3.16, 4.66},
                                   {-0.34, 1.56, 5.76}};
    auto bM = aM;

    EXPECT_TRUE(nearEqual(aM, bM, 0.0001));

    // Assert that they don't share memory
    bM[0][0] = 3.1;
    EXPECT_FALSE(nearEqual(aM, bM, 0.0001));
}

TEST(GenericMatrix, MatTranspose) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 3, 2> bM = aM.T();

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            EXPECT_EQ(aM[row][col], bM[col][row]);
        }
    }

    // Assert that they DO share memory
    bM[0][1] = 4.1;
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            EXPECT_EQ(aM[row][col], bM[col][row]);
        }
    }
}

TEST(GenericMatrix, PNorm) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    EXPECT_TRUE(abs(pNorm(aM, 2.0) - 11.2676528168) < 0.0001);
    EXPECT_TRUE(abs(pNorm(aM, -1.0) - 0.45922287992) < 0.0001);
    EXPECT_TRUE(abs(pNorm(aM, 0.5) - 138.178178396) < 0.0001);
}

TEST(GenericMatrix, Normalize) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    auto aMCopy = aM;
    normalize_inline(aMCopy, 2.0);
    EXPECT_TRUE(abs(pNorm(aMCopy, 2.0) - 1) < 0.0001);

    aMCopy = aM;
    normalize_inline(aMCopy, 0.1);
    EXPECT_TRUE(abs(pNorm(aMCopy, 0.1) - 1) < 0.0001);

    aMCopy = aM;
    normalize_inline(aMCopy, -1.0);
    EXPECT_TRUE(abs(pNorm(aMCopy, -1.0) - 1) < 0.0001);

    aMCopy = aM;
    normalize_inline(aMCopy, -1.0);
    EXPECT_FALSE(abs(pNorm(aMCopy, 2.0) - 1) < 0.0001);
}

TEST(GenericMatrix, HasNanInf) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> bM{{3.3, INFINITY, 6.0},
                                   {1.0, 2.9,      7.1}};
    GenericMatrix<double, 2, 3> cM{{3.3, NAN, 6.0},
                                   {1.0, 2.9, 7.1}};
    GenericMatrix<double, 2, 3> dM{{3.3, NAN,      6.0},
                                   {1.0, INFINITY, 7.1}};

    EXPECT_FALSE(hasNan(aM));
    EXPECT_FALSE(hasInf(aM));

    EXPECT_FALSE(hasNan(bM));
    EXPECT_TRUE(hasInf(bM));

    EXPECT_TRUE(hasNan(cM));
    EXPECT_FALSE(hasInf(cM));

    EXPECT_TRUE(hasNan(dM));
    EXPECT_TRUE(hasInf(dM));
}

TEST(GenericMatrix, MaxMin) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};

    EXPECT_EQ(max(aM), 7.1);
    EXPECT_EQ(min(aM), 1.0);

    std::size_t row, col;
    argMax(aM, row, col);
    EXPECT_EQ(row, 1);
    EXPECT_EQ(col, 2);

    argMin(aM, row, col);
    EXPECT_EQ(row, 1);
    EXPECT_EQ(col, 0);
}

TEST(GenericMatrix, Trace) {
    GenericMatrix<double, 2, 3> aM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1}};

    EXPECT_DOUBLE_EQ(trace(aM), 6.2);

    GenericMatrix<double, 2, 2> bM{{3.3, 4.5},
                                   {1.0, 2.9}};

    EXPECT_DOUBLE_EQ(trace(bM), 6.2);

    GenericMatrix<double, 3, 3> cM{{3.3, 4.5, 6.0},
                                   {1.0, 2.9, 7.1},
                                   {2.0, 3.9, 3.1}};

    EXPECT_DOUBLE_EQ(trace(cM), 9.3);

    GenericMatrix<double, 4, 3> dM{{3.3, 4.5,  6.0},
                                   {1.0, 2.9,  7.1},
                                   {2.0, 3.9,  3.1},
                                   {5.0, 12.9, 1.1}};

    EXPECT_DOUBLE_EQ(trace(dM), 9.3);
}

TEST(GenericMatrix, RotateInline) {
    GenericMatrix<double, 4, 6> aM{{1, 3,  -2, 4, 1, 7},
                                   {2, 6,  0,  5, 2, 5},
                                   {4, 11, 8,  0, 5, 3},
                                   {1, 3,  2,  1, 1, -2}};

    rotate_inline(aM, 1, 3, 180.0);

    std::cout << "STUB!" << std::endl;
    std::cout << aM << std::endl;
}

TEST(GenericMatrix, GaussJordan) {
    GenericMatrix<double, 4, 6> aM{{1, 3,  -2, 4, 1, 7},
                                   {2, 6,  0,  5, 2, 5},
                                   {4, 11, 8,  0, 5, 3},
                                   {1, 3,  2,  1, 1, -2}};

    // gaussJordan_inline(aM);

    std::cout << "STUB!" << std::endl;
    std::cout << aM << std::endl;
}

TEST(GenericMatrix, GaussJordanRREF) {
    GenericMatrix<double, 2, 3> aM{{1, 3, 7},
                                   {3, 4, 11}};

    // gaussJordanRREF_inline(aM);

    std::cout << "STUB!" << std::endl;
    std::cout << aM << std::endl;
}

