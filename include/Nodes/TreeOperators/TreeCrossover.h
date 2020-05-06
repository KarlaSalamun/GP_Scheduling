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
        void set_depth( int depth ) {
            max_depth = depth;
        }
    private:
        int max_depth = 5;
        void swap_nodes( AbstractNode *&root1, AbstractNode *&root2 );
};

#endif //SANTAFE_TREECROSSOVER_H
