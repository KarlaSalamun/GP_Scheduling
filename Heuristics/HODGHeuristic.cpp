//
// Created by karla on 11. 03. 2020..
//

#include <algorithm>
#include "HODGHeuristic.h"

struct {
    bool operator()(Task *a, Task *b) const
    {
        return a->priority < b->priority;
    }
} customLess;

double HODGHeuristic::calculate_priority(Task *&task, std::vector<Task *> pending_tasks)
{
    std::vector<Task *> tmp_list;
    Task *tmp = new Task;
    bool delay = true;
    int late_index;

    for( auto & task : pending_tasks ) {
        task->priority = calculate_edd( task );
    }
    double time = 0;

    std::sort( pending_tasks.begin(), pending_tasks.end(), customLess );
    for( auto & task : pending_tasks ) {
        task->time_started = time;
        time += task->duration;
    }

    while(delay) {
        for( int i=0; i<pending_tasks.size(); i++ ) {
            if( pending_tasks[i]->time_started + pending_tasks[i]->duration > pending_tasks[i]->due_date ) {
                late_index = i;
                break;
            }
        }
        for( int i=0; i<late_index; i++ ) {

        }
    }

}

double HODGHeuristic::calculate_edd(Task *&task)
{
    return 1. / task->due_date;
}
