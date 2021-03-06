//
// Created by karla on 28. 04. 2020..
//

#ifndef GP_SCHEDULING_NSGA_H
#define GP_SCHEDULING_NSGA_H

#include "GeneticAlgorithm.h"

template <typename T>
class NSGA : public GeneticAlgorithm<T> {
public:
    NSGA( CrossoverOperator<T> *crossover, MutationOperator<T> *mutation,
           SelectionOperator<T> *selection, Function<T> *test_function, Function<T> *train_function,
           Population<T> *population, int generation_number, size_t population_size, unsigned int dim_size ) :
           GeneticAlgorithm<T>( crossover, mutation, selection, test_function, train_function, population,
                             generation_number, population_size, dim_size ) {}

    void get_solution ( std::vector<T> &population, T& result );

private:
    void evaluate_population ( std::vector<T> &population );
    std::vector<std::vector<T>> nondominant_sort( std::vector<T> &population );
    bool is_dominant( std::pair<double, double> x, std::pair<double, double> y );
    void grouping_sort( std::vector<T> &front );
};

#endif //GP_SCHEDULING_NSGA_H