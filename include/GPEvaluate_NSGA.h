//
// Created by karla on 28. 04. 2020..
//

#ifndef GP_SCHEDULING_GPEVALUATE_NSGA_H
#define GP_SCHEDULING_GPEVALUATE_NSGA_H

#include <utility>
#include "GPEvaluateHeuristic.h"

class GPEvaluate_NSGA : public GPEvaluateHeuristic {
public:
    GPEvaluate_NSGA( int task_number ) : GPEvaluateHeuristic( task_number ) {}
    std::pair<double, double> get_value_NSGA ( TreeSolution<AbstractNode *> &solution );
};

#endif //GP_SCHEDULING_GPEVALUATE_NSGA_H
