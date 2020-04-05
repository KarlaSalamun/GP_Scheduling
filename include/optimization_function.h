//
// Created by karla on 18. 10. 2019..
//

#ifndef STEEPEST_DESCENT_OPTIMIZATION_FUNCTION_H
#define STEEPEST_DESCENT_OPTIMIZATION_FUNCTION_H
#include <vector>
#include "NumericFunction.h"

class OptimizationFcn {
public:
    virtual std::vector<double> get_solution( std::vector<double> solution, NumericFunction *test_function ) = 0;
};

#endif //STEEPEST_DESCENT_OPTIMIZATION_FUNCTION_H
