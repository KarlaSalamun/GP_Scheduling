//
// Created by karla on 06. 11. 2019..
//

#ifndef GENETIC_ALGORITHM_GENETICALGORITHM_H
#define GENETIC_ALGORITHM_GENETICALGORITHM_H

#include "CrossoverOperator.h"
#include "MutationOperator.h"
#include "SelectionOperator.h"
#include "Solution.h"
#include "../function.h"

using namespace std;

template <typename T>
static int compare_members(const void *m1, const void *m2)
{
    const T* member1 = static_cast<const T *>(m1);
    const T* member2 = static_cast<const T *>(m2);
    return member1->fitness - member2->fitness;
}

template <typename T>
class GeneticAlgorithm  {
    public:
        GeneticAlgorithm( CrossoverOperator<T> *crossover, MutationOperator<T> *mutation,
                SelectionOperator<T> *selection, Function<T> *test_function, Function<T> *train_function,
                int generation_number, size_t population_size, unsigned int dim_size ) :
            crossover(crossover), mutation(mutation), selection(selection), test_function(test_function),
            train_function(train_function), generation_number(generation_number),
            population_size(population_size), dim_size(dim_size) {}

        ~GeneticAlgorithm()
        {
//            delete test_function;
//            delete crossover;
//            delete mutation;
//            delete selection;
        }

        Function<T> *test_function = nullptr;
        Function<T> *train_function = nullptr;
        void get_solution ( std::vector<T> &population, T& result );
        void get_train_solutions( std::vector<double> &solutions );
        void get_test_solutions( std::vector<double> &solutions );
        void set_crossover ( CrossoverOperator<T> *crossover )
        {
            delete this->crossover;
            this->crossover = crossover;
        }
        void set_mutation ( MutationOperator<T> *mutation )
        {
            delete this->mutation;
            this->mutation = mutation;
        }
        void set_selection ( SelectionOperator<T> *selection )
        {
            delete this->selection;
            this->selection = selection;
        }
    private:
        void evaluate_population ( std::vector<T> &population );
        void add_members( std::vector<T> &population,std::vector<T> &members );
        CrossoverOperator<T> *crossover;
        MutationOperator<T> *mutation = nullptr;
        SelectionOperator<T> *selection = nullptr;
        unsigned int generation_number;
        size_t population_size;
        unsigned int dim_size;
        std::vector<double> train_solutions;
        std::vector<double> test_solutions;
};



#endif //GENETIC_ALGORITHM_GENETICALGORITHM_H
