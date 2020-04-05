//
// Created by karla on 06. 11. 2019..
//

#ifndef GENETIC_ALGORITHM_CROSSOVEROPERATOR_H
#define GENETIC_ALGORITHM_CROSSOVEROPERATOR_H
#include <vector>
#include "Solution.h"

template <typename T>
class CrossoverOperator {
    public:
        virtual ~CrossoverOperator() {}
        virtual void get_children( std::vector<T> &parents, std::vector<T> &children ) = 0;
};

#endif //GENETIC_ALGORITHM_CROSSOVEROPERATOR_H
