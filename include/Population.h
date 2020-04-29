//
// Created by karla on 28. 04. 2020..
//

#ifndef GP_SCHEDULING_POPULATION_H
#define GP_SCHEDULING_POPULATION_H

#include <vector>

template <typename T>
class Population {
public:
    Population( int size ) : size( size ) {}
    virtual void create_new_population( std::vector<T> &population ) = 0;

protected:
    int size;
};

#endif //GP_SCHEDULING_POPULATION_H
