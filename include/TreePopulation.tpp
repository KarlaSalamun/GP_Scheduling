//
// Created by karla on 28. 04. 2020..
//
#include "TreePopulation.h"

template <typename T>
void TreePopulation<T>::create_new_population( std::vector<T> &population )
{
    for( int i=0; i<this->size; i++ ) {
        T solution;
        tc->construct_tree_grow( 5, solution.data.first );
        tc->construct_tree_grow( 5, solution.data.second );
        population.push_back( solution );
    }
}
