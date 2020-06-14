//
// Created by karla on 28. 04. 2020..
//

#include "GPEvaluate_NSGA.h"
#include "Simulator.tpp"

void GPEvaluate_NSGA::initialize()
{
    UunifastCreator *tc = new UunifastCreator( task_number, "./../../test_inputs/comparison.txt", false, 20, 4, 2, 1 );
    std::vector<double> utils = { 0.90, 1, 1.1, 1.2, 1.3, 1.4 };

    for( size_t i = 0; i<5; i++) {
        for( size_t j=0; j<utils.size(); j++ ) {
            tc->set_overload( utils[j] );
            tc->set_task_number( 6 );
            do {
                tc->create_test_set(test_tasks);
                tc->compute_hyperperiod( test_tasks );
            } while( tc->get_hyperperiod() > 10000 );
            test_sets.push_back( test_tasks );
            test_tasks.clear();
        }
    }
}

void GPEvaluate_NSGA::get_value_NSGA( TreeSolution<AbstractNode *> &solution, std::pair<double, double> &fitness, bool display )
{
    Scheduler *sched = new Scheduler();
    UunifastCreator *tc = new UunifastCreator( task_number, "./../../test_inputs/comparison.txt", false, 20, 4, 2, 1 );

    Simulator<AbstractNode *> *simulator = new Simulator<AbstractNode *>( 1, 10, tc, sched, true, false );
    simulator->set_heuristic( solution.data );

    std::vector<double> skip;
    std::vector<double> gini;
    std::vector<double> wasted;

    for( auto & element : test_sets ) {
        simulator->set_pending( element );
        tc->compute_hyperperiod( element );
        simulator->set_finish_time( tc->get_hyperperiod() );
        for( auto & sub : element ) {
            sub->initialize_task();
        }
        simulator->run();
        if( display ) {
            simulator->display_info();
        }
        gini.push_back( simulator->compute_gini_coeff() );
        assert( simulator->compute_gini_coeff() == simulator->compute_gini_coeff() );
        assert( simulator->compute_skip_fitness() == simulator->compute_skip_fitness() );
        if( simulator->get_completed() == 0 ) {
            skip.push_back( 0 );
        }
        else {
            skip.push_back( simulator->compute_skip_fitness() );
        }
        wasted.push_back( simulator->get_time_wasted() / tc->get_hyperperiod() );
    }

    if( islessequal( fabs( compute_mean_fitness( skip ) ), 0.1 ) ) {
        fitness = std::make_pair( 10, -10 );
    }

    solution.coev_fitness = compute_mean_fitness( wasted );
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
        assert( values[i]== values[i] );
    }
    return sum / values.size();
}

void GPEvaluate_NSGA::cleanup()
{
    for( size_t i=0; i<test_sets.size(); i++ ) {
        for( size_t j=0; j<test_sets[i].size(); j++ ) {
            delete test_sets[i][j];
        }
    }
}