//
// Created by karla on 10. 03. 2020..
//

#ifndef GP_SCHEDULING_HEURISTICEVALUATOR_H
#define GP_SCHEDULING_HEURISTICEVALUATOR_H

#include <vector>
#include "../Task.h"

class SchedulingHeuristic {
    public:
        virtual double calculate_priority( Task *&task, std::vector<Task *> pending_tasks ) = 0;
        virtual void set_params( std::vector<Task *> tasks ) = 0;
        virtual void set_time( double time, std::vector<Task *> tasks ) = 0;
};


#endif //GP_SCHEDULING_HEURISTICEVALUATOR_H
