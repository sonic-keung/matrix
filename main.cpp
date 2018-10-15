#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>

#include "googlepagerank.hpp"

int main() {

    // open a file
    std::ifstream file;
    file.open("connectivity.txt");

    if (!file) {
        std::cout << "cannot open the file" << std::endl;
    }
    // read the file
    int count;
    std::vector<double> a;
    while (file >> count) {
        a.push_back(count);
    }

    googlePageRank m(a);

    m.importanceMatrix();

    m.stochasticMatrix();

    m.transitionMatrix();

    m.markov();

    m.printMatrix(a);

    return 0;
}