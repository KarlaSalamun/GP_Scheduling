//
// Created by karla on 18. 01. 2020..
//

#ifndef SANTAFE_TREESOLUTION_H
#define SANTAFE_TREESOLUTION_H

#include "Solution.h"
#include "../function.h"

template <typename T>
class TreeSolution : public Solution<T> {
public:
    T data = nullptr;
    double fitness;
    std::pair<double, double> fitness_NSGA;

    TreeSolution( TreeSolution&& sol) : data(sol.data), fitness(sol.fitness)
    {
        sol.data = nullptr;
    }

    TreeSolution& operator = ( TreeSolution&& other )
    {
        if( &other == this ) {
            return *this;
        }
        delete data;
        this->data = other.data;
        other.data = nullptr;
        return *this;
    }

    TreeSolution( const TreeSolution& obj )
    {
        this->copy_data( data, obj.data );
        this->fitness = obj.fitness;
        this->rank = obj.rank;
        this->S = obj.S;
        this->mi = obj.mi;
        this->d = obj.d;
        this->fitness_NSGA = obj.fitness_NSGA;
    }

    TreeSolution<T>&operator = ( const TreeSolution<T>& obj )
    {
        if ( &obj == this ) {
            return *this;
        }
        delete data;
        this->copy_data( data, obj.data );

        return *this;
    }

    double get_fitness(T solution, Function<T> *test_function )
    {
        return test_function->get_value( solution );
    }

    TreeSolution( T data ) : data( data ) {}
    TreeSolution() {}

    void copy_data( T &dest, const T &src );

    ~TreeSolution() {
        delete data;
    }

};


#endif //SANTAFE_TREESOLUTION_H
