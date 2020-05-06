//
// Created by karla on 12. 12. 2019..
//

#ifndef SANTAFE_TREEMUTATION_H
#define SANTAFE_TREEMUTATION_H

#include "MutationOperator.h"
#include "Nodes/AbstractNode.h"
#include "Solution.h"

template <typename T>
class TreeMutation : public MutationOperator<T> {
public:
    virtual ~TreeMutation() {}
    void mutate_solution ( T &solution );
    void set_depth( int depth ) {
        max_depth = depth;
    }
private:
    int max_depth = 3;
    void mutate_tree( AbstractNode *&root );
};


#endif //SANTAFE_TREEMUTATION_H
