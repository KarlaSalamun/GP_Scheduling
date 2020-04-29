//
// Created by karla on 12. 12. 2019..
//

#ifndef SANTAFE_TREESELECTION_H
#define SANTAFE_TREESELECTION_H

#include "SelectionOperator.h"
#include "Nodes/AbstractNode.h"

template <typename  T>
class TreeSelection : public SelectionOperator<T> {
    public:
    virtual ~TreeSelection() {}
    void get_members( std::vector<T> &population, std::vector<T> &members );
    void grouping_tournament( std::vector<T> &population, std::vector<T> &members );
};


#endif //SANTAFE_TREESELECTION_H
