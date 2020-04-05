//
// Created by karla on 11. 03. 2020..
//

#ifndef GP_SCHEDULING_HODGHEURISTIC_H
#define GP_SCHEDULING_HODGHEURISTIC_H

#include "SchedulingHeuristic.h"

class HODGHeuristic : public SchedulingHeuristic {
public:
    double calculate_priority( Task *&task, std::vector<Task *> pending_tasks );
    void set_params( std::vector<Task *> ) {}
    void set_time( double, std::vector<Task *> ) {}
private:
    double calculate_edd( Task *&task );
};


#endif //GP_SCHEDULING_HODGHEURISTIC_H
