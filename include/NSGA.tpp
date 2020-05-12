//
// Created by karla on 28. 04. 2020..
//
#include <algorithm>
#include "NSGA.h"

template <typename T>
void NSGA<T>::evaluate_population ( std::vector<std::vector<T>> &population )
{
    std::pair<double, double> best_fitness{ 1000, 1000 };

    for( size_t i=0; i<population[0].size(); i++ ) {
//        for( size_t j=0; j<10; j++ ) {
//            population[0][i].evaluation_pair = std::make_pair( population[0][i].data, population[1][j].data );
//            this->train_function->get_value_NSGA( population[0][i], population[0][i].fitness_NSGA, false );
//            if( population[0][i].fitness_NSGA.first < best_fitness.first && population[0][i].fitness_NSGA.second < best_fitness.second ) {
//                best_fitness.first = population[0][i].fitness_NSGA.first;
//                best_fitness.second = population[0][i].fitness_NSGA.second;
//            }
//        }
//        population[0][i].fitness_NSGA.first = best_fitness.first;
//        population[0][i].fitness_NSGA.second = best_fitness.second;

        population[0][i].evaluation_pair = std::make_pair( population[0][i].data, population[1][i].data );
        this->train_function->get_value_NSGA( population[0][i], population[0][i].fitness_NSGA, false );
    }

    for( size_t i=0; i<population[1].size(); i++ ) {
//        for( size_t j=0; j<10; j++ ) {
//            population[1][i].evaluation_pair = std::make_pair( population[0][i].data, population[1][j].data );
//            this->train_function->get_value_NSGA( population[1][i], population[1][i].fitness_NSGA, false );
//            if( population[1][i].fitness_NSGA.first < best_fitness.first && population[1][i].fitness_NSGA.second < best_fitness.second ) {
//                best_fitness.first = population[1][i].fitness_NSGA.first;
//                best_fitness.second = population[1][i].fitness_NSGA.second;
//            }
//        }
//        population[1][i].fitness_NSGA.first = best_fitness.first;
//        population[1][i].fitness_NSGA.second = best_fitness.second;
        population[1][i].evaluation_pair = std::make_pair( population[0][i].data, population[1][i].data );
        this->train_function->get_value_NSGA( population[1][i], population[1][i].fitness_NSGA, false );
    }
}

template <typename T>
void NSGA<T>::get_solution ( std::vector<std::vector<T>> &population, std::vector<T>& result )
{
    std::vector<std::vector<T>> offspring(this->dim_size);

    for( size_t i = 0; i<this->dim_size; i++ ) {
        this->population->create_new_population( offspring[i] );
    }

    std::copy( offspring[0].begin(), offspring[0].end(), std::back_inserter( population[0] ) );
    std::copy( offspring[1].begin(), offspring[1].end(), std::back_inserter( population[1] ) );

    for( size_t i=0; i<population[0].size(); i++ ) {
        population[0][i].evaluation_pair = std::make_pair( population[0][i].data, population[1][i].data );
        this->train_function->get_value_NSGA( population[0][i], population[0][i].fitness_NSGA, false );
    }

    for( size_t i=0; i<population[1].size(); i++ ) {
        population[1][i].evaluation_pair = std::make_pair( population[1][i].data, population[0][i].data );
        this->train_function->get_value_NSGA( population[1][i], population[1][i].fitness_NSGA, false );
    }

    for ( size_t gen=0; gen<this->generation_number; gen++ ) {

        for( size_t species=0; species<this->dim_size; species++ ) {

            std::vector<std::vector<T>> fronts = nondominant_sort( population[species] );

            size_t sumsize = 0;
            for( auto & element : fronts ) {
                sumsize += element.size();
            }

            assert( sumsize == population[species].size() );

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
            std::vector<T> tmp_parents;
            this->selection->grouping_tournament( new_parents, parents );
            std::vector<T> new_offspring;
            std::vector<T> children;

            assert( new_parents.size() % 2 == 0 );

            for( i=0; i<new_parents.size()-1; i+=2 ) {
                assert( new_parents[i].data );
                std::copy( new_parents.begin() + i, new_parents.begin() + i + 2, std::back_inserter( tmp_parents ) );
                children.resize( 2 );
                this->crossover->get_children( tmp_parents, children );
                tmp_parents[0].data = nullptr;
                tmp_parents[1].data = nullptr;
                tmp_parents.clear();
                this->mutation->mutate_solution( children[0] );
                this->mutation->mutate_solution( children[1] );
                this->add_members( new_offspring, children );
                children.clear();
            }

            population[i] = new_parents;
            assert( population[i].size() <= 2 * this->population_size );
            offspring[i] = new_offspring;

            std::copy( offspring[i].begin(), offspring[i].end(), std::back_inserter( population[i] ) );
        }

        evaluate_population( population );

        printf( "generation: %zu\tdeviation: %f\tskip factor: %f\n", gen, population[0][0].fitness_NSGA.first, -population[0][0].fitness_NSGA.second );
    }
    evaluate_population(population );

    this->train_function->get_value_NSGA( population[0][0], population[0][0].fitness_NSGA, true );

    result.push_back( std::move( population[0][0] ) );
    result.push_back( std::move( population[1][0] ) );

    population[0][0].data = nullptr;
    population[0][1].data = nullptr;

    result[0].fitness_NSGA = population[0][0].fitness_NSGA;
    result[1].fitness_NSGA = population[1][0].fitness_NSGA;

    printf( "%f\t%f\n", population[0][0].fitness_NSGA.first, -population[0][0].fitness_NSGA.second );
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
        fronts.push_back( std::move( current_front ) );
        std::copy( Q.begin(), Q.end(), std::back_inserter( current_front ) );
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
    if( front.size() == 0 ) {
        return;
    }

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
                static_cast<double>( front[I1[I1.size()-1]].fitness_NSGA.first - front[I1[0]].fitness_NSGA.first );
        front[I1[i]].d += static_cast<double>( front[I2[i+1]].fitness_NSGA.second - front[I2[i-1]].fitness_NSGA.second ) /
                static_cast<double>( front[I2[I1.size()-1]].fitness_NSGA.second - front[I2[0]].fitness_NSGA.second );
    }

    qsort( front.data(), front.size(), sizeof(T), compare_distances<T> );
}
