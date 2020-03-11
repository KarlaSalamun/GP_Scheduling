//
// Created by karla on 10. 03. 2020..
//

#ifndef GP_SCHEDULING_EVALUATEHEURISTIC_H
#define GP_SCHEDULING_EVALUATEHEURISTIC_H

#include <vector>
#include "SchedulingHeuristic.h"
#include "../Task.h"

class EvaluateHeuristic {
    public:
        EvaluateHeuristic() {}
        double calculate_twt();
        std::vector<Task *> pending_tasks;
        SchedulingHeuristic *heuristic;
    private:
        std::vector<Task *> processed_tasks;
        static int compare_priority( const void *t1, const void *t2 );
};


#endif //GP_SCHEDULING_EVALUATEHEURISTIC_H
