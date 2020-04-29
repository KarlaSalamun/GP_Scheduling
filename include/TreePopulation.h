//
// Created by karla on 28. 04. 2020..
//

#ifndef GP_SCHEDULING_TREEPOPULATION_H
#define GP_SCHEDULING_TREEPOPULATION_H

#include "Population.h"
#include "TreeSolution.h"
#include "TreeConstructor.h"

template<typename T>
class TreePopulation : public Population<T> {
public:
    TreePopulation( int size, TreeConstructor *tc ) : Population<T>( size ) {
        this->tc = tc;
    }
    void create_new_population( std::vector<T> &population );
private:
    TreeConstructor *tc;
};

#endif //GP_SCHEDULING_TREEPOPULATION_H
