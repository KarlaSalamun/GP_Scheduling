//
// Created by karla on 28. 04. 2020..
//

#include "GPEvaluate_NSGA.h"
#include "Simulator.tpp"

void GPEvaluate_NSGA::get_value_NSGA( TreeSolution<AbstractNode *> &solution, std::pair<double, double> &fitness, bool display )
{
    Scheduler *sched = new Scheduler();
    UunifastCreator *tc = new UunifastCreator( task_number, "./../../test_inputs/comparison.txt", false, 10, 1, 1, 1 );
    //    tc->create_test_set( test_tasks );
    //    tc->write_tasks( test_tasks );
    tc->load_tasks( test_tasks );
    tc->compute_hyperperiod( test_tasks );

    Simulator<AbstractNode *> *simulator = new Simulator<AbstractNode *>( 1, 10, tc, sched, true, false );
    simulator->set_heuristic( solution.data );
    simulator->load();
    simulator->set_finish_time( tc->get_hyperperiod() );
    simulator->run();

    if( display ) {
        simulator->display_info();
    }

    fitness = std::make_pair( simulator->compute_deviation(), -simulator->compute_skip_fitness() );

    delete simulator;
    delete sched;
    delete tc;
}
