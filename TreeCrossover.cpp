//
// Created by karla on 12. 12. 2019..
//
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "TreeCrossover.h"
#include "TreeConstructor.h"

template <typename T>
void TreeCrossover<T>::get_children( std::vector<T> &parents, std::vector<T> &children ) {

    TreeConstructor *tc = new TreeConstructor();

    int rand_depth = rand() % parents[0].data->depth;
    AbstractNode *random_tree1 = parents[0].data->pick_random(parents[0].data, rand_depth);

    rand_depth = rand() % parents[1].data->depth;
    AbstractNode *random_tree2 = parents[1].data->pick_random(parents[1].data, rand_depth);

    if ( random_tree1->children_number == 0 || random_tree2->children_number == 0 ) {

        children[0] = move(parents[0]);
        children[1] = move(parents[1]);

        if (children[1].data == nullptr) {
            std::cout << "NULL1" << std::endl;
        }
        delete tc;
        return;
    }


    if( parents[0].data->depth - random_tree1->depth + random_tree2->depth > 5 ) {

        children[0] = parents[0];

        if (parents[1].data->depth - random_tree2->depth + random_tree1->depth > 5) {
            children[1]= move( parents[1] );
        } else {
            children[1] = move( parents[0] );
        }
        if (children[1].data == nullptr) {
            std::cout << "NULL2" << std::endl;
        }
        delete tc;
        return;
    }

    else {

        int random_index1 = rand() % random_tree1->children_number;
        int random_index2 = rand() % random_tree2->children_number;
        std::swap(random_tree2->children[random_index2], random_tree1->children[random_index1]);

        tc->rehash_tree(parents[0].data);
        tc->rehash_tree(parents[1].data);

        children[0] = move( parents[0] );
        children[1] = move( parents[1] );

    }
    if (children[1].data == nullptr) {
        std::cout << "NULL3" << std::endl;
    }

    delete tc;
}

