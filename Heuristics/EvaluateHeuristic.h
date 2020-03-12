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
        EvaluateHeuristic( std::vector<Task *> test_tasks ) : test_tasks( std::move( test_tasks ) ) {}
        double calculate_twt();
        SchedulingHeuristic *heuristic{};
    private:
        std::vector<Task *> test_tasks;
        std::vector<Task *> processed_tasks;
        std::vector<Task *> pending_tasks;
};


#endif //GP_SCHEDULING_EVALUATEHEURISTIC_H
