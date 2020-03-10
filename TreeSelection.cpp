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
    std::vector<T> rand_members(5);

    std::shuffle(population.begin(), population.begin() + 10, std::default_random_engine());

    for (int i = 0; i < rand_members.size(); i++) {
        rand_members[i] = population[i];
        rand_members[i].fitness = population[i].fitness;
    }

    qsort(rand_members.data(), rand_members.size(), sizeof(T), compare_members<Solution<AbstractNode *>>);

    members[0] = move(rand_members[0]);
    members[1] = move(rand_members[1]);
}

