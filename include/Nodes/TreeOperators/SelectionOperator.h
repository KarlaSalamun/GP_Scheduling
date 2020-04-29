//
// Created by karla on 13. 11. 2019..
//

#ifndef GENETIC_ALGORITHM_SELECTIONOPERATOR_H
#define GENETIC_ALGORITHM_SELECTIONOPERATOR_H

#include "Solution.h"

template <typename T>
class SelectionOperator {
    public:
        virtual ~SelectionOperator() {}
        virtual void get_members( std::vector<T> &population, std::vector<T> &members ) = 0;
        virtual void grouping_tournament( std::vector<T> &population, std::vector<T> &members ) = 0;
};


#endif //GENETIC_ALGORITHM_SELECTIONOPERATOR_H
