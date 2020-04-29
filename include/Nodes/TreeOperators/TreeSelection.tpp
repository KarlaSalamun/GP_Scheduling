//
// Created by karla on 12. 12. 2019..
//

#include <algorithm>
#include <random>
#include <cstdlib>
#include <cassert>
#include "TreeSelection.h"
#include "GeneticAlgorithm.h"

template <typename T>
void TreeSelection<T>::get_members( std::vector<T> &population, std::vector<T> &members ) {
    std::vector<T> rand_members;

    std::shuffle(population.begin(), population.begin() + 10, std::default_random_engine());

    for (int i = 0; i < 5; i++) {
        rand_members.push_back( population[i] );
    }

    qsort(rand_members.data(), rand_members.size(), sizeof(T), compare_members<Solution<AbstractNode *>>);

    members[0] = move(rand_members[0]);
    members[1] = move(rand_members[1]);
}

template <typename T>
void TreeSelection<T>::grouping_tournament( std::vector<T> &population, std::vector<T> &members )
{
    members.clear();

    for( size_t i=0; i<population.size(); i++ ) {
        for( size_t j=0; j< population.size(); j++ ) {
            if( j == i ) {
                continue;
            }
            if( population[i].rank > population[j].rank ) {
                members.push_back( population[i] );
                continue;
            }
            if( population[i].rank == population[j].rank && population[i].d > population[j].d ) {
                members.push_back( population[i] );
            }
        }
    }
}
