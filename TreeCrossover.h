//
// Created by karla on 12. 12. 2019..
//

#ifndef SANTAFE_TREECROSSOVER_H
#define SANTAFE_TREECROSSOVER_H

#include "CrossoverOperator.h"
#include "Nodes/AbstractNode.h"

template <typename  T>
class TreeCrossover : public CrossoverOperator<T> {
    public:
        virtual ~TreeCrossover() {}
        void get_children( std::vector<T> &parents, std::vector<T> &children );
};

#endif //SANTAFE_TREECROSSOVER_H
