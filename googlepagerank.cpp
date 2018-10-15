#include <iostream>
#include <iomanip>
#include <cmath>
#include "googlepagerank.hpp"

// divides each value in each column by the sum of each column
void googlePageRank::importanceMatrix() {
    matrix matrixS(*this);

    for(int i = 0; i < matrices[0].size(); i++) {
        double colSum = 0;
        for(int j = 0; j < matrices[i].size(); j++) {
            colSum += matrixS.get_value(j, i);
        }

        if(colSum == 0) {
            ;
        } else {
            for (int k = 0; k < matrices.size(); k++) {
                matrices[k][i] /= colSum;
            }
        }
    }
}

// divides the value in each column by the sum of each column
void googlePageRank::stochasticMatrix() {
    matrix matrixS(*this);

    for(int i = 0; i < matrices.size(); i++) {
        double colSum = 0;
        for(int j = 0; j < matrices[i].size(); j++) {
            colSum += matrixS.get_value(j, i);
        }
        if (colSum == 0) {
            for (int k = 0; k < matrices.size(); k++) {
                matrices[k][i] = 1.0 / matrices.size();
            }
        }
    }
}

// adds (1- 0.85) multiplied by matrixQ, where Q's every element is 1/n
void googlePageRank::transitionMatrix() {
    matrix matrixQ(matrices.size());
    matrix matrixM(matrices.size());
    matrix matrixS(matrices.size());

    for(int i = 0; i < matrices.size(); i++){
        for(int j = 0; j < matrices[i].size(); j++){
            matrixQ.set_value(i, j, 1.0 / matrices[j].size());
        }
    }
    std::cout << matrixQ << std::endl;

    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < matrices[i].size(); j++) {
            double newQVal = matrixQ.get_value(i, j) * (1 - p);
            matrixQ.set_value(i, j, newQVal);
        }
    }
    std::cout << matrixQ << std::endl;
    for(int i = 0; i < matrices[0].size(); i++) {
        for(int j = 0; j < matrices[i].size(); j++) {
            double newSVal = matrices[i][j] * p;
            matrixS.set_value(i, j, newSVal);
        }
    }
    std::cout << matrixS << std::endl;

    matrixM = matrixS + matrixQ;
    std::cout << matrixM << std::endl;
}

// markov process
void googlePageRank::markov() {
    matrix matrixM(matrices.size());
    matrix rank(matrices.size(), 1);
    matrix oldRank(matrices.size());

    while(oldRank != rank){
        oldRank = rank;
        rank = matrixM * rank;
    }

    for(int i = 0; i < rank.get_row(); i++){
        for(int j = 0; j < rank.get_col(); j++){
            sumOfRank += rank.get_value(i, j);
            rank.set_value(i, j, 1);
        }
    }
    std::cout << rank << std::endl;

    for(int i = 0; i < rank.get_row(); i++){
        for(int j = 0; j < rank.get_col(); j++){
            double newVal = (rank.get_value(i, j) / sumOfRank) * 100;
            rank.set_value(i, j, newVal);
        }
    }
    matrices = rank.getMatrix();
}

// displays the rank matrix
// use ascii values 65
void googlePageRank::printMatrix(const std::vector<double> &arr) {
    int asciiCharacters = 65;
    for(int i = 0; i < matrices.size(); i++) {
        for(int j = 0; j < matrices[i].size(); j++) {
            std::cout << "Page " << (char) asciiCharacters << ": " << std::fixed
                      << std::setprecision(2) << matrices[i][j] * 100 << "%" << std::endl;
            asciiCharacters++;
        }
        std::cout << std::endl;
    }
}

