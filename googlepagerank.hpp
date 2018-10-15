#include <iostream>
#include <vector>
#include "matrix.hpp"

class googlePageRank : public matrix {
    double sumOfRank = 0;

public:
    static constexpr double p = 0.85;
    googlePageRank() : matrix(){};
    googlePageRank(std::vector<double> a) : matrix(a){};

    void stochasticMatrix();
    void transitionMatrix();
    void importanceMatrix();
    void markov();
    void printMatrix(const std::vector<double> &arr);

};
