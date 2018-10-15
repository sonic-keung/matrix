#include <iostream>
#include <string.h>
#include <iomanip>
#include <cmath>
#include <vector>

#include "matrix.hpp"

// create a 1 by 1 matrix
matrix::matrix() {
    matrices = {1, std::vector<double>(1, 0.0)};
    clear();
}

// accepts size of matrix and set all values to zero
matrix::matrix(int n) {
    if (n <= 0) {
        throw "Error: positive integers expected";
    }

    matrices = {(unsigned long) n, std::vector<double>(n, 0.0)};
    clear();
}

// create matrix to be r x c
matrix::matrix(int r, int c) {
    if (r <= 0 || c <= 0) {
        throw "Error: row and column positive";
    }

    matrices = {(unsigned long)r, std::vector<double>(c, 0.0)};
    clear();
}

// create matrix using double vector
matrix::matrix(std::vector<double> m) {
    if (sqrt(m.size()) != sqrt(m.size())) {
        throw "error";
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
    if (r < 0 || r >= matrices.size()) {
        throw "row and column must be less than 0";
    }
    matrices[r][c] = newValue;
}

// get the value of matrix
double matrix::get_value(int r, int c) const {
    if (r < 0 || c < 0) {
        throw "row or column must be less than 0";
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
    if (matrices.size() != rhs.matrices.size()) {
        throw "matrix sizes are not the same";
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
    if (matrices.size() != rhs.matrices.size()) {
        throw "matrix sizes are not the same";
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
    if (matrices[0].size() != rhs.matrices.size()) {
        throw "# of columns of first operand not equal to # of rows of second operand";
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