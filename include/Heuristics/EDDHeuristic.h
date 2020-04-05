//
// Created by karla on 11. 03. 2020..
//

#ifndef GP_SCHEDULING_EDDHEURISTIC_H
#define GP_SCHEDULING_EDDHEURISTIC_H

#include "SchedulingHeuristic.h"

class EDDHeuristic : public SchedulingHeuristic {
public:
    EDDHeuristic() = default;
    double calculate_priority( Task *&task, std::vector<Task *> pending_tasks );
    void set_params( std::vector<Task *> tasks ) {}
    void set_time( double time, std::vector<Task *> tasks ) {}
};


#endif //GP_SCHEDULING_EDDHEURISTIC_H
