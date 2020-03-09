//
// Created by karla on 06. 03. 2020..
//
#include <queue>
#include <chrono>
#include "EvaluateHeuristic.h"

double EvaluateHeuristic::get_value( TreeSolution<AbstractNode *> &solution )
{
    Task hp_task;
    double twt = 0;
    double time = 0;

    hp_task = pending_tasks[0];
    hp_task.priority = pending_tasks[0].priority;

    while( pending_tasks.size() > 0 ) {
        for( int i=0; i<pending_tasks.size(); i++ ) {
            pending_tasks[i].priority = solution.calculate_priority( pending_tasks[i], pending_tasks );
            if( pending_tasks[i].priority > hp_task.priority ) {
                hp_task = pending_tasks[i];
                hp_task.priority = pending_tasks[i].priority;
            }
        }
        twt += hp_task.compute_tardiness() * hp_task.weight;
        qsort( pending_tasks, pending_tasks.size(), sizeof( Task ), compare_priority );
        processed_tasks.push_back( pending_tasks.begin() );
        pending_tasks.erase( pending_tasks.begin() );

        time+=hp_task.duration;
        // sortirati po prioritetu
        // izracunati tardiness prvog
        // maknuti ga iz pending
        // staviti ga u processed
        // uvecati time za njegov processing time
    }
    return twt;
}

double EvaluateHeuristic::compare_priority( const void *t1, const void *t2 )
{
    const Task *task1 = static_cast<const Task*>(t1);
    const Task *task2 = static_cast<const Task*>(t2);

    return task1->priority - task2->priority;
}