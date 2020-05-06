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

    TreeSolution( TreeSolution&& sol)
    {
        copy_data( this->data.first, sol.data.first );
        copy_data( this->data.second, sol.data.second );
        this->fitness = sol.fitness;
        sol.data.first = nullptr;
        sol.data.second = nullptr;
    }

    TreeSolution() = default;

    TreeSolution& operator = ( TreeSolution&& other )
    {
        if( &other == this ) {
            return *this;
        }
//        delete this->data;
        this->data.first = std::move( other.data.first );
        this->data.second = std::move( other.data.second );
//        other.data = nullptr;
        return *this;
    }

    TreeSolution( const TreeSolution& obj )
    {
        this->copy_data( this->data.first, obj.data.first );
        this->copy_data( this->data.second, obj.data.second );

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
        delete this->data.first;
        delete this->data.second;
        this->copy_data( this->data.first, obj.data.first );
        this->copy_data( this->data.second, obj.data.second );

        return *this;
    }

    double get_fitness(T solution, Function<T> *test_function )
    {
        return test_function->get_value( solution );
    }

    TreeSolution( T data ) {
        this->data.first = data.first;
        this->data.second = data.second;

    }

    void copy_data( T &dest, const T &src );

    ~TreeSolution() {
        if( this->data.first && this->data.second ) {
            delete this->data.first;
            delete this->data.second;
        }
    }
};


#endif //SANTAFE_TREESOLUTION_H
