//
// Created by karla on 06. 03. 2020..
//
#include <queue>
#include <chrono>
#include <cstdio>
#include <algorithm>
#include <UunifastCreator.h>
#include "Simulator.h"
#include "Simulator.tpp"
#include "AbstractNode.h"
#include "GPEvaluateHeuristic.h"

double GPEvaluateHeuristic::get_value( TreeSolution<AbstractNode *> &solution )
{
    double twt = 0;
    double abs_time = 0;

    Scheduler *sched = new Scheduler();
    UunifastCreator *tc = new UunifastCreator( task_number, "./../../test_inputs/160.txt", false, 10, 1, 1, 1 );
//    tc->create_test_set( test_tasks );
//    tc->write_tasks( test_tasks );
    tc->load_tasks( test_tasks );
    tc->compute_hyperperiod( test_tasks );

    if( periodic ) {
        Simulator<AbstractNode *> *simulator = new Simulator<AbstractNode *>( 1, 10, tc, sched, true, false );
        simulator->set_heuristic( solution.evaluation_pair );
        simulator->load();
        simulator->set_finish_time( tc->get_hyperperiod() );
        simulator->run();
        return simulator->compute_skip_fitness();
//        return simulator->get_total_tardiness();
    }

    else {
        while( pending_tasks.size() > 0 ) {
            for (size_t i = 0; i < pending_tasks.size(); i++) {
                pending_tasks[i]->set_priority( solution.data->calculate_priority(
                        reinterpret_cast<Task *&>(pending_tasks[i]),
                        reinterpret_cast<const std::vector<Task *> &>(pending_tasks),
                        reinterpret_cast<const std::vector<Task *> &>(processed_tasks)) );
            }

            std::sort( pending_tasks.begin(), pending_tasks.end(),
                       []( const Task *a, const Task *b ) -> bool { return a->get_priority() < b->get_priority(); });
            pending_tasks[0]->set_time_started( abs_time );
            twt += pending_tasks[0]->compute_tardiness( abs_time ) * pending_tasks[0]->get_weight();
            abs_time += pending_tasks[0]->get_duration();
            processed_tasks.push_back(pending_tasks[0]);
            pending_tasks.erase(pending_tasks.begin());
        }
        return twt;
    }
}
