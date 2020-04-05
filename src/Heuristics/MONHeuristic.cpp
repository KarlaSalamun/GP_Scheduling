//
// Created by karla on 10. 03. 2020..
//
#include <cmath>
#include "MONHeuristic.h"

double MONHeuristic::calculate_priority( Task *&task, std::vector<Task *> )
{
    return task->get_weight() / task->get_duration()  / ( 1 - task->get_abs_due_date() / total_pt );
}

void MONHeuristic::set_params( std::vector<Task *> tasks )
{
    total_pt = 0;
    for( size_t i=0; i<tasks.size(); i++ ) {
        total_pt += tasks[i]->get_duration();
    }
}