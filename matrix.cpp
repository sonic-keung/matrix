#include <iostream>
#include <string.h>
#include <iomanip>
#include <cmath>
#include <vector>

#include "matrix.hpp"

// create a 1 by 1 matrix
matrix::matrix() : row{1}, col{1}{
    matrices = {(unsigned long)row, std::vector<double>(col, 0.0)};
    clear();
}

// accepts size of matrix and set all values to zero
matrix::matrix(int n) : row {n}, col {n} {
    try {
        if (n <= 0)
            throw std::invalid_argument("Error: positive integers expected");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    matrices = {(unsigned long) row, std::vector<double>(col, 0.0)};
    clear();
}

// create matrix to be r x c
matrix::matrix(int r, int c) : row{r}, col{c} {
    try {
        if (r <= 0 || c <= 0)
            throw std::invalid_argument("Error: row and column positive");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    matrices = {(unsigned long)row, std::vector<double>(col, 0.0)};
    clear();
}

// create matrix using double vector
matrix::matrix(std::vector<double> m) {
    try {
        if (sqrt(m.size()) != sqrt(m.size()))
            throw std::invalid_argument("Error: size of the array does not have an integer square root ");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    matrices = {(unsigned long) sqrt(m.size()), std::vector<double>(sqrt(m.size()), 0.0)};
    int index = 0;
    for(int i = 0; i < matrices.size(); i++) {
        for(int j = 0; j < matrices[i].size(); j++) {
            matrices[i][j] = m[index];
            index++;
        }
    }
}

// copy constructor
matrix::matrix(const matrix& m) {
    this->matrices = m.matrices;
}

// set the value of each matrix
void matrix::set_value(int r, int c, double newValue) {
    try {
        if (r < 0 || r >= matrices.size() || c < 0 || c >= matrices.size())
            throw std::invalid_argument("Error: integers are negative or too large ");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    matrices[r][c] = newValue;
}

// get the value of matrix
double matrix::get_value(int r, int c) const {
    try {
        if (r < 0 || r >= matrices.size() || c < 0 || c >= matrices.size())
            throw std::invalid_argument("Error: integers are negative or too large ");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    return matrices[r][c];
}

// clear matrix
void matrix::clear() {
    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < matrices[i].size(); j++) {
            matrices[i][j] = 0.0;
        }
    }
}

// swap values of the matrices
void swap(matrix& lhs, matrix& rhs) {
    using std::swap;
    swap(lhs.matrices, rhs.matrices);
}

// destructor
matrix::~matrix() = default;

// overloaded increment operator
matrix& matrix::operator++() {
    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < matrices[i].size(); j++) {
            matrices[i][j]++;
        }
    }
    return *this;
}

// overloaded postincrement operator
matrix matrix::operator++(int) {
    matrix temp(*this);
    operator++();
    return temp;
}

// overloaded decrement operator
matrix& matrix::operator--() {
    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < matrices[i].size(); j++) {
            matrices[i][j]--;
        }
    }
    return *this;
}

// overloaded post decrement operator
matrix matrix::operator--(int) {
    matrix temp(*this);
    operator--();
    return temp;
}

// overloaded assignment operator
matrix& matrix::operator=(matrix rhs) {
    swap(*this, rhs);
    return *this;
}

// overloaded assignment operator
matrix& matrix::operator+=(const matrix& rhs) {
    try {
        if (matrices.size() != rhs.matrices.size())
            throw std::invalid_argument("Error: operands passed to the operator are not same size");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < rhs.matrices[i].size(); j++) {
            matrices[i][j] += rhs.matrices[i][j];
        }
    }
    return *this;
}

// overloaded assignment operator
matrix& matrix::operator-=(const matrix& rhs) {
    try {
        if (matrices.size() != rhs.matrices.size())
            throw std::invalid_argument("Error: operands passed to the operator are not same size");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < rhs.matrices[i].size(); j++) {
            matrices[i][j] -= rhs.matrices[i][j];
        }
    }
    return *this;
}

// overloaded assignment operator
matrix& matrix::operator*=(const matrix& rhs) {
    try {
        if (matrices[0].size() != rhs.matrices.size())
            throw std::invalid_argument("Error: # of columns of first operand not equal to # of rows of second operand");

    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    matrix tempMatrix(matrices.size(), rhs.matrices.size());

    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < matrices[i].size(); j++) {
            double sum = 0;
            for (int k = 0; k < matrices[i].size(); k++ ) {
                sum += matrices[i][k] * rhs.matrices[k][j];
            }
            tempMatrix.set_value(i, j, sum);
        }
    }
    matrices = tempMatrix.matrices;
    return *this;
}

// overloaded insertion operator
std::ostream& operator<<(std::ostream& os, const matrix& matrix) {
    for (int i = 0; i < matrix.matrices.size(); i++) {
        for (int j = 0; j < matrix.matrices[i].size(); j++) {
            os << std::setw(5) << matrix.matrices[i][j];
        }
        os << "\n";
    }

    return os;
}

// overloaded equality operator
bool operator==(const matrix& lhs, const matrix& rhs) {
    if (lhs.matrices.size() != rhs.matrices.size()) {
        return false;
    }

    for (int i = 0; i < lhs.matrices.size(); i++) {
        for (int j = 0; j < lhs.matrices[i].size(); j++) {
            if (fabs(lhs.matrices[i][j] - rhs.matrices[i][j]) > matrix::TOLERANCE) {
                return false;
            }
        }
    }
    return true;
}

// overloaded not equal operator
bool operator!=(const matrix& lhs, const matrix& rhs) {
    return !operator==(lhs, rhs);
}

// overloaded addition operator
matrix operator+(matrix lhs, const matrix& rhs) {
    lhs += rhs;
    return lhs;
}

// overloaded subtraction operator
matrix operator-(matrix lhs, const matrix& rhs) {
    lhs -= rhs;
    return lhs;
}

// overloaded multiplication operator
matrix operator*(matrix lhs, const matrix& rhs) {
    lhs *= rhs;
    return lhs;
}

int matrix::get_row() {
    return row;
}

int matrix::get_col() {
    return col;
}

std::vector<std::vector<double>> matrix::getMatrix() {
    return matrices;
}