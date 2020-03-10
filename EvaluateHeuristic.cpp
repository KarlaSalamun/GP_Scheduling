//
// Created by karla on 06. 03. 2020..
//
#include <queue>
#include <chrono>
#include <cstdio>
#include <algorithm>
#include "EvaluateHeuristic.h"

struct {
    bool operator()(Task *a, Task *b) const
    {
        return a->priority < b->priority;
    }
} customLess;

double EvaluateHeuristic::get_value( TreeSolution<AbstractNode *> &solution )
{
    TaskCreator *tc = new TaskCreator( 10, 1, 1 );
    // TaskCreator( int task_number, double dd_range, double dd_tightness )

    Task *hp_task;
    double twt = 0;
    double time = 0;

    tc->create_test_set( pending_tasks );

    hp_task = pending_tasks[0];
    hp_task->priority = 0;

    while( pending_tasks.size() > 0 ) {
        for( int i=0; i<pending_tasks.size(); i++ ) {
            pending_tasks[i]->priority = solution.data->calculate_priority( pending_tasks[i], pending_tasks, processed_tasks );
            if( pending_tasks[i]->priority > hp_task->priority ) {
                hp_task = pending_tasks[i];
                hp_task->priority = pending_tasks[i]->priority;
            }
        }
        hp_task->time_started = time;
        twt += hp_task->compute_tardiness() * hp_task->weight;

        std::sort( pending_tasks.begin(), pending_tasks.end(), customLess );

        processed_tasks.push_back( pending_tasks[0] );
        pending_tasks.erase( pending_tasks.begin() );

        time+=hp_task->duration;
        // sortirati po prioritetu
        // izracunati tardiness prvog
        // maknuti ga iz pending
        // staviti ga u processed
        // uvecati time za njegov processing time
    }
    return twt;
}

int EvaluateHeuristic::compare_priority( const void *t1, const void *t2 )
{
    const Task *task1 = static_cast<const Task*>(t1);
    const Task *task2 = static_cast<const Task*>(t2);

    return static_cast<int>(task1->priority - task2->priority);
}