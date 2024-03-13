//
// Created by Theo Lincke on 1/20/24.
//

#ifndef MATLIBCPP_GENERICMATRIX_H
#define MATLIBCPP_GENERICMATRIX_H

#include <array>
#include <sstream>
#include <valarray>
#include <memory>
#include <GenericMatrixSlice.h>
#include <Matrix.h>

namespace mcpp {
    // Requires C++20 with upgraded g++
    /**
    template<typename P>
    concept MatElem = requires(P a, P b) { a + b; a - b; a * b; a / b; a < b; a > b; };
     */
    template<typename P, std::size_t R, std::size_t C>
    class GenericMatrix : public Matrix {
    public:
        ///////// CONSTRUCTORS
        // Initializes everything to 0
        GenericMatrix();

        // Shares underlying data - use this sparingly
        explicit GenericMatrix(std::shared_ptr<std::array<P, C * R>> &_data);

        // Initializes data
        GenericMatrix(const std::initializer_list<std::initializer_list<P>> &_data);

        // Copies data
        GenericMatrix(const GenericMatrix &rhs);

        GenericMatrixSlice<P, R, C> operator[](int i);

        GenericMatrixSlice<P, R, C> operator[](int i) const;

        friend std::ostream &operator<<(std::ostream &os, GenericMatrix<P, R, C> const &tc) {
            return os << tc.print();
        }

        GenericMatrix<P, R, C> &operator*=(const P &x);

        GenericMatrix<P, R, C> operator*(const P &x) const;

        template<std::size_t K>
        GenericMatrix<P, R, K> operator*(const GenericMatrix<P, C, K> &x) const;

        GenericMatrix<P, R, C> &operator*=(const GenericMatrix<P, C, C> &x);

        GenericMatrix<P, R, C> operator+(const P &x) const;

        GenericMatrix<P, R, C> &operator+=(const P &x);

        GenericMatrix<P, R, C> operator+(const GenericMatrix<P, R, C> &x) const;

        GenericMatrix<P, R, C> &operator+=(const GenericMatrix<P, R, C> &x);

        GenericMatrix<P, R, C> operator-(const P &x) const;

        GenericMatrix<P, R, C> &operator-=(const P &x);

        GenericMatrix<P, R, C> operator-(const GenericMatrix<P, R, C> &x) const;

        GenericMatrix<P, R, C> &operator-=(const GenericMatrix<P, R, C> &x);

        GenericMatrix<P, R, C> &operator=(const GenericMatrix<P, R, C> &x);

        bool operator==(const GenericMatrix<P, R, C> &x) const;

        bool operator!=(const GenericMatrix<P, R, C> &x) const;

        GenericMatrix<P, C, R> T();

        void make_transpose();

    private:
        [[nodiscard]] std::string print() const;

        bool isTranspose{false};

        std::shared_ptr<std::array<P, C * R>> data;

        void data_init();
    };

    template<typename P, size_t R, size_t C>
    GenericMatrix<P, R, C> ident();

    template<typename Z, size_t M, size_t N>
    bool nearEqual(const GenericMatrix<Z, M, N> &left, const GenericMatrix<Z, M, N> &right, Z epsilon);

    template<typename P, size_t M, size_t N, size_t K>
    GenericMatrix<P, M, K> matMul(const GenericMatrix<P, M, N> &left, const GenericMatrix<P, N, K> &right);

    template<typename P, size_t R, size_t C>
    void scalMul_inline(GenericMatrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    void matAdd_inline(GenericMatrix<P, R, C> &left, const GenericMatrix<P, R, C> &right);

    template<typename P, size_t R, size_t C>
    void scalAdd_inline(GenericMatrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    void matSub_inline(GenericMatrix<P, R, C> &left, const GenericMatrix<P, R, C> &right);

    template<typename P, size_t R, size_t C>
    void scalSub_inline(GenericMatrix<P, R, C> &left, const P &right);

    template<typename P, size_t R, size_t C>
    P pNorm(const GenericMatrix<P, R, C> &m, P p);

    template<typename P, size_t R, size_t C>
    void normalize_inline(GenericMatrix<P, R, C> &m, P p);

    template<typename P, size_t R, size_t C>
    bool hasNan(const GenericMatrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    bool hasInf(const GenericMatrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void argMax(const GenericMatrix<P, R, C> &m, std::size_t &row, std::size_t &col);

    template<typename P, size_t R, size_t C>
    P max(const GenericMatrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void argMin(const GenericMatrix<P, R, C> &m, std::size_t &row, std::size_t &col);

    template<typename P, size_t R, size_t C>
    P min(const GenericMatrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    P trace(const GenericMatrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void rotate_inline(GenericMatrix<P, R, C> &m, std::size_t x, std::size_t y, double theta);

    template<typename P, size_t R, size_t C>
    void gaussJordan_inline(GenericMatrix<P, R, C> &m);

    template<typename P, size_t R, size_t C>
    void gaussJordanRREF_inline(GenericMatrix<P, R, C> &m);
}

#include "../src/GenericMatrix.tpp"

#endif //MATLIBCPP_GENERICMATRIX_H
