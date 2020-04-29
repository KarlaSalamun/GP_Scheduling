//
// Created by karla on 28. 04. 2020..
//
#include <algorithm>
#include "NSGA.h"

template <typename T>
void NSGA<T>::evaluate_population ( std::vector<T> &population )
{
    for( size_t i = 0; i<population.size(); i++ ) {
        population[i].fitness_NSGA = this->train_function->get_value_NSGA( population[i] );
    }
}

template <typename T>
void NSGA<T>::get_solution ( std::vector<T> &population, T& result )
{
    std::vector<T> offspring;
    this->population->create_new_population( offspring );

    for ( size_t gen=0; gen<this->generation_number; gen++ ) {
        std::copy( offspring.begin(), offspring.end(), std::back_inserter( population ) );

        evaluate_population( population );

        std::vector<std::vector<T>> fronts = nondominant_sort( population );

        std::vector<T> new_parents;
        size_t remaining_size = this->population_size;
        size_t i;
        for( i=0; i<fronts.size(); i++ ) {
            if( fronts[i].size() > remaining_size ) {
                break;
            }
            remaining_size -= fronts[i].size();
            std::copy( fronts[i].begin(), fronts[i].end(), std::back_inserter( new_parents ) );
        }

        grouping_sort( fronts[i] );
        std::copy( fronts[i].begin(), fronts[i].begin()+remaining_size, std::back_inserter( new_parents )  );

        std::vector<T> parents;
        std::vector<T> tmp_parents(2);
        this->selection->grouping_tournament( new_parents, parents );
        std::vector<T> new_offspring;
        std::vector<T> children(2);

        for( i=0; i<new_parents.size(); i+=2 ) {
            tmp_parents[0] = new_parents[i];
            tmp_parents[1] = new_parents[i+1];
            this->crossover->get_children( tmp_parents, children );
            this->mutation->mutate_solution( children[0] );
            this->mutation->mutate_solution( children[1] );
            this->add_members( new_offspring, children );
        }

        population = new_parents;
        offspring = new_offspring;

        printf( "generation: %zu\ttardiness: %f\tmissed: %f\n", gen, population[0].fitness_NSGA.first, population[0].fitness_NSGA.second );
    }
    evaluate_population(population );
    result = move( population[0] );
    result.fitness_NSGA = population[0].fitness_NSGA;
}

template <typename T>
std::vector<std::vector<T>> NSGA<T>::nondominant_sort( std::vector<T> &population )
{
    std::vector<T> current_front;
    std::vector<std::vector<T>> fronts;
    int front_cnt;
    for( size_t i=0; i<population.size(); i++ ) {
        population[i].mi = 0;
        population[i].S.clear();
        for( size_t j=0; j<population.size(); j++ ) {
            if( i == j ) {
                continue;
            }
            if( is_dominant( population[i].fitness_NSGA, population[j].fitness_NSGA ) ) {
                population[i].S.push_back( j );
            }
            else if( is_dominant( population[j].fitness_NSGA, population[i].fitness_NSGA ) ) {
                population[i].mi++;
            }
        }
        if( population[i].mi == 0 ) {
            population[i].rank = 1;
            current_front.push_back( population[i] );
            front_cnt = 1;
        }
    }

    while( !current_front.empty() ) {
        front_cnt++;
        fronts.push_back( current_front );
        std::vector<T> Q;
        for( size_t i = 0; i<current_front.size(); i++ ) {
            for( size_t j=0; j<current_front[i].S.size(); j++ ) {
                population[current_front[i].S[j]].mi--;
                if( population[current_front[i].S[j]].mi == 0 ) {
                    population[current_front[i].S[j]].rank = front_cnt;
                    Q.push_back( population[current_front[i].S[j]] );
                }
            }
        }
        current_front = Q;
    }

    return fronts;
}

template <typename T>
bool NSGA<T>::is_dominant( std::pair<double, double> x, std::pair<double, double> y )
{
    if( x.first <= y.first && x.second <= y.second ) {
        if( x.first < y.first || x.second < y.second ) {
            return true;
        }
    }
    return false;
}

template <typename T>
void NSGA<T>::grouping_sort( std::vector<T> &front )
{
    std::vector<int> I1( front.size() );
    std::vector<int> I2( front.size() );

    for( size_t i=0; i<front.size(); i++ ) {
        I1[i] = i;
        I2[i] = i;
    }

    for( auto & element : front ) {
        element.d = 0;
    }

    std::sort( I1.begin(), I1.end(),
              [&front](int a, int b)
                      -> bool { return front[a].fitness_NSGA.first < front[b].fitness_NSGA.first; });

    std::sort( I2.begin(), I2.end(),
               [&front](int a, int b)
                       -> bool { return front[a].fitness_NSGA.second < front[b].fitness_NSGA.second; });

    front[I1[0]].d = front[I1[I1.size()-1]].d = 100;
    front[I2[0]].d = front[I2[I2.size()-1]].d = 100;

    for( size_t i=1; i<I1.size()-1; i++ ) {
        front[I1[i]].d = static_cast<double>( front[I1[i+1]].fitness_NSGA.first - front[I1[i-1]].fitness_NSGA.first ) /
                static_cast<double>( front[I1[5]].fitness_NSGA.first - front[I1[0]].fitness_NSGA.first );
        front[I1[i]].d += static_cast<double>( front[I2[i+1]].fitness_NSGA.second - front[I2[i-1]].fitness_NSGA.second ) /
                static_cast<double>( front[I2[5]].fitness_NSGA.second - front[I2[0]].fitness_NSGA.second );
    }
    std::sort( front.begin(), front.end(),
               []( const auto &a, const auto &b )
                       -> bool { return a.d > b.d; });
}