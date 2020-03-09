//
// Created by karla on 06. 11. 2019..
//

#ifndef GENETIC_ALGORITHM_MUTATIONOPERATOR_H
#define GENETIC_ALGORITHM_MUTATIONOPERATOR_H

#include <vector>

template <typename T>
class MutationOperator {
public:
    virtual void mutate_solution ( T &solution ) = 0;
    virtual ~MutationOperator() {}
};


#endif //GENETIC_ALGORITHM_MUTATIONOPERATOR_H
