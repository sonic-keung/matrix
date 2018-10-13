#include <iostream>
#include <string.h>
#include <iomanip>
#include <cmath>

#include "matrix.hpp"

// create a 1 by 1 matrix
matrix::matrix() : row{1}, col{1} {
    int dimensions = (row * col);
    matrices = new double[dimensions];
    clear();
}

matrix::matrix(int n) : row {n}, col {n} {
    if (n <= 0) {
        throw "Error: positive integers expected";
    }

    matrices = new double[row * col];
    clear();
}

// create matrix to be r x c
matrix::matrix(int r, int c) : row {r}, col{c} {
    if (r <= 0 || c <= 0) {
        throw "Error: row and column positive";
    }

    matrices = new double[row * col];
    clear();
}

matrix::matrix(double n[], int m) : row {m}, col{m} {
    int dimension = m;
    row = (int)sqrt(dimension);
    col = (int)sqrt(dimension);
    if (row * col != m) {
        throw "invalid size";
    }
    matrices = new double[row * col * row * col];
    for (int i = 0; i < m; i++) {
        matrices[i] = n[i];
    }
}

matrix::matrix(const matrix& m) {
    this->matrices = m.matrices;
}

void matrix::set_value(int r, int c, double newValue) {
    if (r < 0 || r > newValue || c < 0 || c > newValue) {
        throw "row and column must be less than 0";
    }
    int index = (r * col + c);
    matrices[index] = newValue;

}

double matrix::get_value(int r, int c) const {
    if (r < 0 || c < 0) {
        throw "row or column must be less than 0";
    }
    int index = (r * col + c);
    return matrices[index];
}

void matrix::clear() {
    for (int i = 0; i < row * col; i++) {
        matrices[i] = 0.0;
    }
}

void swap(matrix& lhs, matrix& rhs) {
    using std::swap;
    swap(lhs.row, rhs.row);
    swap(lhs.col, rhs.col);
    swap(lhs.matrices, rhs.matrices);
}

matrix::~matrix() {
    delete[] matrices;
}

matrix& matrix::operator++() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < col; j++) {
            set_value(i, j, get_value(i, j) + 1);
        }
    }
    return *this;
}

matrix matrix::operator++(int) {
    matrix temp(*this);
    operator++();
    return temp;
}

matrix& matrix::operator--() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            set_value(i, j, get_value(i, j) - 1);
        }
    }
    return *this;
}

matrix matrix::operator--(int) {
    matrix temp(*this);
    operator--();
    return temp;
}

matrix& matrix::operator=(matrix rhs) {
    swap(*this, rhs);
    return *this;
}

matrix& matrix::operator+=(const matrix& rhs) {
    for (int i = 0; i < row * col; i++) {
        for (int j = 0; j < row * col; j++) {
            this->matrices[i * (row * col) + j] +=
                    rhs.matrices[i * (row * col) + j];
        }
    }
    return *this;
}

matrix& matrix::operator-=(const matrix& rhs) {
    for (int i = 0; i < row * col; i++) {
        for (int j = 0; j < row * col; j++) {
            this->matrices[i * (row * col) + j] -=
                    rhs.matrices[i * (row * col) + j];
        }
    }
    return *this;
}

matrix& matrix::operator*=(const matrix& rhs) {
    matrix tempMatrix(row, rhs.col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < rhs.col; j++) {
            float sum = 0;
            for (int k = 0; k < col; k++ ) {
                sum += get_value(i, k) * rhs.get_value(k, j);
            }
            tempMatrix.set_value(i, j, sum);
        }
    }
    this->matrices = tempMatrix.matrices;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const matrix& matrix) {
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.col; j++) {
            os << std::setw(5) << matrix.matrices[i * matrix.col + j];
        }
        os << "\n";
    }

    return os;
}

bool operator==(const matrix& lhs, const matrix& rhs) {
    if (lhs.row != rhs.row || lhs.col != rhs.col) {
        return false;
    }

    for (int i = 0; i < lhs.row; i++) {
        for (int j = 0; j < lhs.col; j++) {
            if (fabs(lhs.get_value(i, j) - rhs.get_value(i, j)) > matrix::TOLERANCE) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const matrix& lhs, const matrix& rhs) {
    return operator==(lhs, rhs);
}

matrix operator+(matrix lhs, const matrix& rhs) {
    lhs += rhs;
    return lhs;
}

matrix operator-(matrix lhs, const matrix& rhs) {
    lhs -= rhs;
    return lhs;
}

matrix operator*(matrix lhs, const matrix& rhs) {
    lhs *= rhs;
    return lhs;
}




