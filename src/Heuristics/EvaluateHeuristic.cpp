//
// Created by karla on 10. 03. 2020..
//

#include <algorithm>
#include "EvaluateHeuristic.h"
#include "StaticCreator.h"

struct {
    bool operator()(Task *a, Task *b) const
    {
        return a->get_priority() < b->get_priority();
    }
} customLess;

double EvaluateHeuristic::calculate_twt()
{

    pending_tasks = test_tasks;

    StaticCreator *tc = new StaticCreator( 0.6, 0.6 );
    tc->set_task_number( 50 );

    double twt = 0;
    double time = 0;

    //tc->create_test_set( pending_tasks );

    heuristic->set_params( pending_tasks );

    while( pending_tasks.size() > 0 ) {
        heuristic->set_time( time, pending_tasks );
        for( size_t i=0; i<pending_tasks.size(); i++ ) {
            pending_tasks[i]->set_priority( heuristic->calculate_priority( pending_tasks[i], pending_tasks ) );
        }

        std::sort( pending_tasks.begin(), pending_tasks.end(), customLess );

        pending_tasks[0]->set_time_started( time );
        twt += pending_tasks[0]->compute_tardiness( time ) * pending_tasks[0]->get_weight();

        time+=pending_tasks[0]->get_duration();

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