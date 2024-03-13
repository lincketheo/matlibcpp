//
// Created by Theo Lincke on 1/20/24.
//

#ifndef MATLIBCPP_GENERICMATRIX_H
#define MATLIBCPP_GENERICMATRIX_H

#include <array>
#include <sstream>
#include <valarray>
#include <memory>
#include <MatrixSlice.h>

namespace mcpp {
    // Requires C++20 with upgraded g++
    /**
    template<typename P>
    concept MatElem = requires(P a, P b) { a + b; a - b; a * b; a / b; a < b; a > b; };
     */
    template<typename P, std::size_t R, std::size_t C>
    class Matrix {
    public:
        ///////// CONSTRUCTORS
        // Initializes everything to 0
        Matrix();

        // Shares underlying data - use this sparingly
        explicit Matrix(std::shared_ptr<std::array<P, C * R>> &_data);

        // Initializes data
        Matrix(const std::initializer_list<std::initializer_list<P>> &_data);

        // Copies data
        Matrix(const Matrix &rhs);

        MatrixSlice<P, R, C> operator[](int i);

        MatrixSlice<P, R, C> operator[](int i) const;

        friend std::ostream &operator<<(std::ostream &os, Matrix<P, R, C> const &tc) {
            return os << tc.print();
        }

        Matrix<P, R, C> &operator*=(const P &x);

        Matrix<P, R, C> operator*(const P &x) const;

        template<std::size_t K>
        Matrix<P, R, K> operator*(const Matrix<P, C, K> &x) const;

        Matrix<P, R, C> &operator*=(const Matrix<P, C, C> &x);

        Matrix<P, R, C> operator+(const P &x) const;

        Matrix<P, R, C> &operator+=(const P &x);

        Matrix<P, R, C> operator+(const Matrix<P, R, C> &x) const;

        Matrix<P, R, C> &operator+=(const Matrix<P, R, C> &x);

        Matrix<P, R, C> operator-(const P &x) const;

        Matrix<P, R, C> &operator-=(const P &x);

        Matrix<P, R, C> operator-(const Matrix<P, R, C> &x) const;

        Matrix<P, R, C> &operator-=(const Matrix<P, R, C> &x);

        Matrix<P, R, C> &operator=(const Matrix<P, R, C> &x);

        bool operator==(const Matrix<P, R, C> &x) const;

        bool operator!=(const Matrix<P, R, C> &x) const;

        Matrix<P, C, R> T();

        void make_transpose();

    private:
        [[nodiscard]] std::string print() const;

        bool isTranspose{false};

        std::shared_ptr<std::array<P, C * R>> data;

        void data_init();
    };

    template<typename P, size_t R, size_t C>
    Matrix<P, R, C> ident();

    template<typename Z, size_t M, size_t N>
    bool nearEqual(const Matrix<Z, M, N> &left, const Matrix<Z, M, N> &right, Z epsilon);

    template<typename P, size_t M, size_t N, size_t K>
    Matrix<P, M, K> matMul(const Matrix<P, M, N> &left, const Matrix<P, N, K> &right);

    template<typename P, size_t R, size_t C>
    void scalMul_inline(Matrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    void matAdd_inline(Matrix<P, R, C> &left, const Matrix<P, R, C> &right);

    template<typename P, size_t R, size_t C>
    void scalAdd_inline(Matrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    void matSub_inline(Matrix<P, R, C> &left, const Matrix<P, R, C> &right);

    template<typename P, size_t R, size_t C>
    void scalSub_inline(Matrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    P pNorm(const Matrix<P, R, C> &m, P p);

    template<typename P, size_t R, size_t C>
    void normalize_inline(Matrix<P, R, C> &m, P p);

    template<typename P, size_t R, size_t C>
    bool hasNan(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    bool hasInf(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void argMax(const Matrix<P, R, C> &m, std::size_t &row, std::size_t &col);

    template<typename P, size_t R, size_t C>
    P max(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void argMin(const Matrix<P, R, C> &m, std::size_t &row, std::size_t &col);

    template<typename P, size_t R, size_t C>
    P min(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    P trace(const Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void rotate_inline(Matrix<P, R, C> &m, std::size_t x, std::size_t y, double theta);

    template<typename P, size_t R, size_t C>
    void gaussJordan_inline(Matrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void gaussJordanRREF_inline(Matrix<P, R, C> &m);
}

#include "../src/Matrix.tpp"

#endif //MATLIBCPP_GENERICMATRIX_H
