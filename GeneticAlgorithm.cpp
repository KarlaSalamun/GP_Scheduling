//
// Created by karla on 06. 11. 2019..
//

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "GeneticAlgorithm.h"
#include "Solution.h"
#include "Solution.cpp"

using namespace std;

template <typename T>
 void GeneticAlgorithm<T>::evaluate_population(std::vector<T> &population )
{
    for ( size_t i=0; i<population.size(); i++ ) {
        population[i].fitness = test_function->get_value( population[i] );
    }

    qsort( population.data(), population.size(), sizeof(T), compare_members<T> );

}

template <typename T>
void GeneticAlgorithm<T>::add_members( std::vector<T> &population, std::vector<T>& members )
{
    for( int i=0; i<members.size(); i++ ) {
        population.push_back(move(members[i]));
    }
}


template <typename T>
void GeneticAlgorithm<T>::get_solution ( std::vector<T> &population, T& result )
{

    for ( size_t i=0; i<generation_number; i++ ) {
        std::vector<T> best_members(2);
        std::vector<T> parents(2);
        std::vector<T> children(2);
        std::vector<T> new_population;

        evaluate_population(population );

        best_members[0] = population[0];
        best_members[1] = population[1];

        add_members( new_population, best_members );

        evaluate_population( new_population );

        while( new_population.size() < population.size() ) {

            selection->get_members( population, parents );

            crossover->get_children( parents, children );

            mutation->mutate_solution( children[0] );
            mutation->mutate_solution( children[1] );

            add_members(new_population, children );
        }

        population.clear();
        for ( size_t j=0; j<new_population.size(); j++ ) {
            population.push_back(move(new_population[j]));
        }
        printf("generation[%lu]\tbest members: %f %f \n", i, population[0].fitness, population[1].fitness );
    }
    evaluate_population(population );
    result = move( population[0] );
}


