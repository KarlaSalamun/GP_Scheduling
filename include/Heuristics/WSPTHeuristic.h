//
// Created by karla on 10. 03. 2020..
//

#ifndef GP_SCHEDULING_WSPTHEURISTIC_H
#define GP_SCHEDULING_WSPTHEURISTIC_H

#include "SchedulingHeuristic.h"

class WSPTHeuristic  : public SchedulingHeuristic {
public:
    double calculate_priority( Task *&task, std::vector<Task *> pending_tasks );
    void set_params( std::vector<Task *> ) {}
    void set_time( double, std::vector<Task *> ) {}
};

#endif //GP_SCHEDULING_WSPTHEURISTIC_H
