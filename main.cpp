#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>

#include "googlepagerank.hpp"

int main() {

    // open a file
    std::ifstream file;
    file.open("connectivity.txt");

    // check if file is unavailable
    if(!file) {
        std::cout << "cannot open file" << std::endl;
    }

    // read the file
    int count;
    std::vector<double> a;
    while (file >> count) {
        a.push_back(count);
    }

    googlePageRank m(a);

    std::cout << m << std::endl;

    m.importanceMatrix();
    std::cout << m << std::endl;

    m.stochasticMatrix();
    std::cout << m << std::endl;

    m.transitionMatrix();

    m.markov();

    m.printMatrix(a);

    return 0;
}