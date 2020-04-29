//
// Created by karla on 28. 04. 2020..
//

#include "GPEvaluate_NSGA.h"

std::pair<double, double> GPEvaluate_NSGA::get_value_NSGA( TreeSolution<AbstractNode *> &solution )
{
    Scheduler *sched = new Scheduler();
    UunifastCreator *tc = new UunifastCreator( task_number, "./../../test_inputs/task_set.txt", false, 10, 1, 1, 1 );
    //    tc->create_test_set( test_tasks );
    //    tc->write_tasks( test_tasks );
    tc->load_tasks( test_tasks );
    tc->compute_hyperperiod( test_tasks );

    Simulator<AbstractNode *> *simulator = new Simulator<AbstractNode *>( 1, 10, tc, sched, true );
    simulator->set_heuristic( solution.data );
    simulator->load();
    simulator->set_finish_time( tc->get_hyperperiod() );
    simulator->run();

    return std::make_pair( simulator->get_total_tardiness(), simulator->get_missed() );
}

