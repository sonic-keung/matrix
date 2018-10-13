#include <iostream>
#include "matrix.hpp"

int main() {

    std::cout << "initalize a 3 x 3 matrix" << std::endl;
    matrix matrix_test1{ 3 };
    std::cout << matrix_test1 << std::endl << "\n";

    std::cout << "add values to the matrix" << std::endl;
    double array_test[] {1.0, 2.0, 3.0, 4.0};
    matrix matrix_test2{array_test, 4};
    std::cout << matrix_test2 << std::endl;

    double array_test2[] {1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0};

    matrix matrix_test3 {array_test2, 9};
    std::cout << matrix_test3 << std::endl;

    std::cout << "\n" << "setting and getting values of a matrix" << std::endl;

    std::cout << matrix_test3.get_value(0,0) << ": this is 1.0" << std::endl;
    std::cout << matrix_test3.get_value(0,1) << ": this is 2.0" << std::endl;

    matrix_test3.set_value(0, 0, 99);
    std::cout << matrix_test3.get_value(0,0) << ": matrix at 0,0 is set to 99.0" << std::endl;

    matrix matrix_test4{3};
    matrix matrix_test5{3};

    std::cout << "\n" << "testing comparison operators" << std::endl;
    if (matrix_test4 == matrix_test5) {
        std::cout << "pass" << std::endl;
    } else {
        std::cout << "failed" << std::endl;
    }

    if (matrix_test4 != matrix_test5) {
        std::cout << "failed" << std::endl;
    } else {
        std::cout << "pass" << std::endl;
    }

    double test[] = {1.0, 2.0, 3.0, 4.0};
    double test2[] = {1.0, 2.0, 3.0, 4.0};

    matrix matrix_test6(test, 4);
    matrix matrix_test7(test2, 4);

    std::cout << "\n" << "multiplying matrices" << std::endl;
    std::cout << (matrix_test6 *= matrix_test7) << std::endl;
    std::cout << (matrix_test6 += matrix_test7) << std::endl;
    std::cout << (matrix_test6 -= matrix_test7) << std::endl;


    std::cout << "\n" << "increment operators" << std::endl;
    double array_test4[] {1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0};
    matrix matrix_test8{array_test4, 9};
    std::cout << matrix_test8 << std::endl;

    matrix_test8++;
    std::cout << matrix_test8 << std::endl;

    std::cout << "\n" << "decrement operator" << std::endl;
    double array_test5[] {1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0};
    matrix matrix_test9{array_test5, 9};
    std::cout << matrix_test9 << std::endl;

    matrix_test9--;
    std::cout << matrix_test9 << std::endl;

    return 0;

}