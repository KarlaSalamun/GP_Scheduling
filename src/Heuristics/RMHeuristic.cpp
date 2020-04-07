//
// Created by karla on 10. 03. 2020..
//
#include <cmath>

#include "RMHeuristic.h"

double RMHeuristic::calculate_priority(Task *&task, std::vector<Task *> ) {

    //return task->weight / task->duration *
     //   std::max( 1 - std::max( task->due_date - task->duration , 0. ) / ( 1 * mean_pt ) , 0. );

    return task->get_weight() / task->get_duration() *
        exp( -1 * std::max( task->get_abs_due_date() - task->get_duration() - time, 0. ) / ( 2 * mean_duration_unprocessed ) );
}

void RMHeuristic::set_params(std::vector<Task *> tasks )
{
    double sum = 0;
    for(auto & task : tasks) {
        sum += task->get_duration();
    }
    mean_pt = sum / tasks.size();
}

void RMHeuristic::set_time( double time, std::vector<Task *> tasks )
{
    this->time = time;
    mean_duration_unprocessed = 0;
    for(auto & task : tasks) {
        mean_duration_unprocessed += task->get_duration();
    }
    mean_duration_unprocessed /= tasks.size();
}
