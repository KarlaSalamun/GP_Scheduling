//
// Created by karla on 10. 03. 2020..
//

#include <algorithm>
#include "EvaluateHeuristic.h"
#include "../TaskCreator.h"

struct {
    bool operator()(Task *a, Task *b) const
    {
        return a->priority < b->priority;
    }
} customLess;

double EvaluateHeuristic::calculate_twt()
{
    TaskCreator *tc = new TaskCreator( 50, 0.6, 0.6 );
    // TaskCreator( int task_number, double dd_range, double dd_tightness )

    double twt = 0;
    double time = 0;

    tc->create_test_set( pending_tasks );

    heuristic->set_params( pending_tasks );

    while( pending_tasks.size() > 0 ) {
        heuristic->set_time( time, pending_tasks );
        for( int i=0; i<pending_tasks.size(); i++ ) {
            pending_tasks[i]->priority = heuristic->calculate_priority( pending_tasks[i], pending_tasks );
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
};