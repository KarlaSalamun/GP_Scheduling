//
// Created by karla on 28. 04. 2020..
//

#include "GPEvaluate_NSGA.h"
#include "Simulator.tpp"

void GPEvaluate_NSGA::get_value_NSGA( TreeSolution<AbstractNode *> &solution, std::pair<double, double> &fitness, bool display )
{
    Scheduler *sched = new Scheduler();
    UunifastCreator *tc = new UunifastCreator( task_number, "./../../test_inputs/test_1.txt", false, 30, 10, 5, 1 );
    //    tc->create_test_set( test_tasks );
    //    tc->write_tasks( test_tasks );
//    tc->load_tasks( test_tasks );
//    tc->compute_hyperperiod( test_tasks );

    Simulator<AbstractNode *> *simulator = new Simulator<AbstractNode *>( 1, 10, tc, sched, true, false );
    simulator->set_heuristic( solution.data );
//    simulator->load();
//    simulator->set_finish_time( tc->get_hyperperiod() );
//    simulator->run();
//

    std::vector<double> skip;
    std::vector<double> gini;

    std::vector<double> utils = { 0.90, 1, 1.1, 1.2, 1.3, 1.4 };

    for( size_t i = 0; i<5; i++) {
        for( size_t j=0; j<utils.size(); j++ ) {
            tc->set_overload( utils[j] );
            tc->set_task_number( 6 );
            tc->create_test_set( test_tasks );
            tc->compute_hyperperiod( test_tasks );
            simulator->set_pending( test_tasks );
            simulator->set_finish_time( tc->get_hyperperiod() );
            simulator->run();
            if( display ) {
                simulator->display_info();
            }
            gini.push_back( simulator->compute_gini_coeff() );
            skip.push_back( simulator->compute_skip_fitness() );
        }
    }

    fitness = std::make_pair( compute_mean_fitness( gini ), -compute_mean_fitness( skip ) );

    delete simulator;
    delete sched;
    delete tc;
}

double GPEvaluate_NSGA::compute_mean_fitness( std::vector<double> values )
{
    double sum = 0;
    for( size_t i=0; i<values.size(); i++ ) {
        sum += values[i];
    }
    return sum / values.size();
}