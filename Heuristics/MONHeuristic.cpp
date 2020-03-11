//
// Created by karla on 10. 03. 2020..
//
#include <cmath>
#include "MONHeuristic.h"

double MONHeuristic::calculate_priority( Task *&task, std::vector<Task *> pending_tasks )
{
    return task->weight / task->duration  / ( 1 - task->due_date / total_pt );
}

void MONHeuristic::set_params( std::vector<Task *> tasks )
{
    total_pt = 0;
    for( int i=0; i<tasks.size(); i++ ) {
        total_pt += tasks[i]->duration;
    }
}