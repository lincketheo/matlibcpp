//
// Created by Theo Lincke on 1/20/24.
//

#ifndef MATLIBCPP_MATRIX_H
#define MATLIBCPP_MATRIX_H

#include <array>
#include <sstream>
#include <valarray>
#include <memory>
//#include <concepts>

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

        /**
         * A Wrapper around an array that indexes rows / columns
         * as if they're contiguous
         */
        class Slice {
        public:
            Slice() = delete;

            Slice(int _index, bool _isCol, std::shared_ptr<std::array<P, C * R>> _data);

            P &operator[](int i) {
                int ii = i;
                if (ii < 0) {
                    ii += C;
                }
                if (ii >= C) {
                    std::stringstream ss;
                    ss << "Invalid col index: " << i << " for matrix with " << C << " cols";
                    throw std::invalid_argument(ss.str());
                }
                if (isCol) {
                    return (*data)[R * ii + index];
                } else {
                    return (*data)[index * C + ii];
                }
            }

        private:
            bool isCol;
            int index;
            std::shared_ptr<std::array<P, C * R>> data;
        };

        Slice operator[](int i) {
            int ii = i;
            if (ii < 0) {
                ii += R;
            }
            if (ii >= R) {
                std::stringstream ss;
                ss << "Invalid row index: " << i << " for matrix with " << R << " rows";
                throw std::invalid_argument(ss.str());
            }
            if (isTranspose) {
                return Slice(ii, true, data);
            } else {
                return Slice(ii, false, data);
            }
        }

        Slice operator[](int i) const {
            int ii = i;
            if (ii < 0) {
                ii += R;
            }
            if (ii >= R) {
                std::stringstream ss;
                ss << "Invalid row index: " << i << " for matrix with " << R << " rows";
                throw std::invalid_argument(ss.str());
            }
            if (isTranspose) {
                return Slice(ii, true, data);
            } else {
                return Slice(ii, false, data);
            }
        }

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

        template<typename Z, size_t M, size_t N>
        friend bool nearEqual(const Matrix<Z, M, N> &left, const Matrix<Z, M, N> &right, Z epsilon);

        Matrix<P, C, R> T();

        void make_transpose();

    private:
        [[nodiscard]] std::string print() const;

        bool isTranspose{false};

        std::shared_ptr<std::array<P, C * R>> data;

        void data_init();
    };
}

#include "../src/operators.tpp"
#include "../src/Matrix.tpp"


#endif //MATLIBCPP_MATRIX_H
