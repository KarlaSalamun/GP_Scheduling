//
// Created by karla on 12. 12. 2019..
//
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "TreeCrossover.h"
#include "TreeConstructor.h"

template <typename T>
void TreeCrossover<T>::get_children( std::vector<T> &parents, std::vector<T> & )
{
    swap_nodes( parents[0].data.first, parents[1].data.first );
    swap_nodes( parents[0].data.second, parents[1].data.second );
}

template <typename T>
void TreeCrossover<T>::swap_nodes( AbstractNode *&root1, AbstractNode *&root2 )
{
    TreeConstructor *tc = new TreeConstructor();

    int rand_depth = rand() % root1->depth;
    AbstractNode *random_tree1 = root1->pick_random(root1, rand_depth);
    tc->get_depth( random_tree1 );

    rand_depth = rand() % root2->depth;
    AbstractNode *random_tree2 = root2->pick_random( root2, rand_depth );
    tc->get_depth( random_tree2 );

    if ( random_tree1->children_number == 0 || random_tree2->children_number == 0 ) {
        delete tc;
        return;
    }

    if( root1->depth - random_tree1->depth + random_tree2->depth > max_depth ||
        root2->depth - random_tree2->depth + random_tree1->depth > max_depth ) {
        delete  tc;
        return;
    }

    else {
        int random_index1 = rand() % random_tree1->children_number;
        int random_index2 = rand() % random_tree2->children_number;
        std::swap(random_tree2->children[random_index2], random_tree1->children[random_index1]);

        tc->rehash_tree(root1);
        tc->rehash_tree(root2);
    }
    delete tc;
}
