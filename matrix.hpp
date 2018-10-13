#include <iostream>

class matrix {
private:
    double* matrices;
    int row;
    int col;
    static constexpr double TOLERANCE = 0.001;

public:
    matrix();
    matrix(int);
    matrix(int, int);
    matrix(double[], int);
    void set_value(int, int, double);
    double get_value(int, int) const;
    void clear();
    matrix(const matrix&);
    friend void swap(matrix&, matrix&);
    ~matrix();

    matrix& operator++();
    matrix operator++(int);
    matrix& operator--();
    matrix operator--(int);
    matrix& operator=(matrix);
    matrix& operator+=(const matrix&);
    matrix& operator-=(const matrix&);
    matrix& operator*=(const matrix&);
    friend std::ostream& operator << (std::ostream&, const matrix&);
    friend bool operator==(const matrix&, const matrix&);
    friend bool operator!=(const matrix&, const matrix&);
    friend matrix operator+(matrix, const matrix&);
    friend matrix operator-(matrix, const matrix&);
    friend matrix operator*(matrix, const matrix&);

};