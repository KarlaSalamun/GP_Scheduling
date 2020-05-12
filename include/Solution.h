//
// Created by karla on 13. 11. 2019..
//

#ifndef PROJEKT_SOLUTION_H
#define PROJEKT_SOLUTION_H

#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

template <typename  T>
class Solution {
    public:
        T data;
        double fitness;
        std::pair<double, double> fitness_NSGA;
        int mi;
        std::vector<int> S;
        double d;
        int rank;
        std::pair<T, T> evaluation_pair;
};

#endif //PROJEKT_SOLUTION_H
