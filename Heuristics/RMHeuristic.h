//
// Created by karla on 10. 03. 2020..
//

#ifndef GP_SCHEDULING_RMHEURISTICEVALUATOR_H
#define GP_SCHEDULING_RMHEURISTICEVALUATOR_H

#include <vector>
#include "SchedulingHeuristic.h"

class RMHeuristic  : public SchedulingHeuristic {
public:
    double calculate_priority( Task *&task, std::vector<Task *> pending_tasks );
    void set_params( std::vector<Task *> tasks );
    void set_time( double time, std::vector<Task *> tasks );
private:
    double mean_pt;
    double time;
    double mean_duration_unprocessed;           // mean duration of unproccessed tasks
};


#endif //GP_SCHEDULING_RMHEURISTICEVALUATOR_H
