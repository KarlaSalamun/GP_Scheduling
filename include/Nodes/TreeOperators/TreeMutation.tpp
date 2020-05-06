//
// Created by karla on 12. 12. 2019..
//

#include <cstdlib>
#include <queue>
#include <iostream>
#include "TreeMutation.h"
#include "TreeConstructor.h"

// replaces random node with randomly generated subtree

template <typename T>
void TreeMutation<T>::mutate_solution ( T &solution )
{
    mutate_tree( solution.data.first );
    mutate_tree( solution.data.second );
}

template <typename T>
void TreeMutation<T>::mutate_tree( AbstractNode *&root )
{
    AbstractNode *new_node;

    TreeConstructor *tc = new TreeConstructor();
/*
    if( rand() % 2 ) {
        tc->construct_tree_grow(rand() % MAX_SUBTREE_DEPTH + 1, new_node );
        solution.data->replace_random( new_node );
    }
    else {
        tc->construct_tree_full(rand() % MAX_SUBTREE_DEPTH + 1, new_node );
        solution.data->replace_random( new_node );
    }
*/
    tc->construct_tree_grow( rand() % max_depth + 1, new_node );

    root->replace_random( new_node );
    delete new_node;

    tc->rehash_tree( root );
    delete tc;
}