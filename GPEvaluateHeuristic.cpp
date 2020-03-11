//
// Created by karla on 06. 03. 2020..
//
#include <queue>
#include <chrono>
#include <cstdio>
#include <algorithm>
#include "GPEvaluateHeuristic.h"

struct {
    bool operator()(Task *a, Task *b) const
    {
        return a->priority < b->priority;
    }
} customLess;

double GPEvaluateHeuristic::get_value(TreeSolution<AbstractNode *> &solution )
{
    TaskCreator *tc = new TaskCreator( 50, 0.6, 0.6 );
    // TaskCreator( int task_number, double dd_range, double dd_tightness )
    double twt = 0;
    double time = 0;

    tc->create_test_set( pending_tasks );

    while( pending_tasks.size() > 0 ) {
        for( int i=0; i<pending_tasks.size(); i++ ) {
            pending_tasks[i]->priority = solution.data->calculate_priority( pending_tasks[i], pending_tasks, processed_tasks );
        }

        std::sort( pending_tasks.begin(), pending_tasks.end(), customLess );

        pending_tasks[0]->time_started = time;
        twt += pending_tasks[0]->compute_tardiness() * pending_tasks[0]->weight;

        time+=pending_tasks[0]->duration;

        processed_tasks.push_back( pending_tasks[0] );
        pending_tasks.erase( pending_tasks.begin() );

        // sortirati po prioritetu
        // izracunati tardiness prvog
        // maknuti ga iz pending
        // staviti ga u processed
        // uvecati time za njegov processing time
    }
    return twt;
}

int GPEvaluateHeuristic::compare_priority(const void *t1, const void *t2 )
{
    const Task *task1 = static_cast<const Task*>(t1);
    const Task *task2 = static_cast<const Task*>(t2);

    return static_cast<int>(task1->priority - task2->priority);
}