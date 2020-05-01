//
// Created by karla on 18. 01. 2020..
//

#include "TreeSolution.h"
#include "Nodes/AbstractNode.h"

template <typename T>
void TreeSolution<T>::copy_data( T &dest, const T &src )
{

    std::queue<AbstractNode *> queue_src;
    std::queue<AbstractNode *> queue_dest;

    assert( src->children[0] );

    src->copy_node( dest );
    queue_src.push( src );
    queue_dest.push( dest );

    while ( !queue_dest.empty() ) {
        AbstractNode *current_src = queue_src.front();
        queue_src.pop();

        AbstractNode *current_dest = queue_dest.front();
        queue_dest.pop();

        for (int i = 0; i < current_src->children_number; i++) {
            current_src->children[i]->copy_node(current_dest->children[i] );
            queue_src.push( current_src->children[i] );
            queue_dest.push( current_dest->children[i] );
        }
    }
}