//
// Created by karla on 19. 01. 2020..
//

#ifndef STEEPEST_DESCENT_NUMERICFUNCTION_H
#define STEEPEST_DESCENT_NUMERICFUNCTION_H

#include <vector>

class NumericFunction {
    public:
        virtual double get_value( std::vector<double> &args ) = 0;
        virtual std::vector<double> get_gradient_approximation(std::vector<double> args, double delta) = 0;
};


#endif //STEEPEST_DESCENT_NUMERICFUNCTION_H
