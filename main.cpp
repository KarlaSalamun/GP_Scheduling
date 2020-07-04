#include <memory>
#include "TreeConstructor.h"
#include "TreeSolution.h"
#include "GPEvaluateHeuristic.h"
#include "GeneticAlgorithm.h"
#include "TreeMutation.h"
#include "TreeSelection.h"
#include "TreeCrossover.h"
#include "TreeMutation.tpp"
#include "TreeCrossover.tpp"
#include "TreeSelection.tpp"
#include "TreeSolution.tpp"
#include "GeneticAlgorithm.tpp"
#include "src/GPEvaluateHeuristic.cpp"
#include "Heuristics/EvaluateHeuristic.h"
#include "Heuristics/RMHeuristic.h"
#include "Heuristics/MONHeuristic.h"
#include "Heuristics/WSPTHeuristic.h"
#include "Heuristics/EDDHeuristic.h"
#include "Heuristics/HODGHeuristic.h"
#include "matplotlibcpp.h"
#include "GPEvaluate_NSGA.h"
#include "NSGA.tpp"
#include "TreePopulation.tpp"


namespace plt = matplotlibcpp;

void generate_csv(std::vector<double> results, std::vector<double> utils, std::string filename );
void test_utils_qos( AbstractNode * heuristic );
void test_utils_wCPU( AbstractNode * heuristic );
void pareto_test( AbstractNode * heuristic );

int main( void )
{
    TreeSolution<AbstractNode *>result;
//    srand(static_cast<double> (0));
    srand(static_cast<double> (time(NULL)) );

    TreeConstructor *tc = new TreeConstructor();
//
    int population_size = 40;
    TreePopulation<TreeSolution<AbstractNode *>> *tp =
            new TreePopulation<TreeSolution<AbstractNode *>>( population_size, tc );
    std::vector<TreeSolution<AbstractNode *>> population;
    tp->create_new_population( population );

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    GPEvaluate_NSGA *nsga = new GPEvaluate_NSGA( 3 );
    nsga->create_test_set();
    GPEvaluate_NSGA *nsga1 = new GPEvaluate_NSGA( 3 );
    nsga1->create_test_set();
//
    auto *ga = new NSGA<TreeSolution<AbstractNode *>>( crossover,
            mutation, selection, nsga, nsga1, tp, 30, population_size, 0 );

    ga->get_solution( population, result );

    tc->draw_tree( result.data, "../graphs/skipfactoropt.dot" );
   return 0;
}

void generate_csv(std::vector<double> results, std::vector<double> utils, std::string filename )
{
    std::string tmp = "./../../test_outputs/";
    FILE *fd = fopen( (tmp + filename).c_str(), "w+" );
    for( size_t i=0; i<results.size(); i++ ) {
        fprintf( fd, "%lf,%lf\n", utils[i], results[i] );
    }
    fclose( fd );
}

void test_utils_qos( AbstractNode * heuristic )
{
    UunifastCreator *taskc = new UunifastCreator( 3, "./../../test_inputs/test_1.txt", true, 20, 4, 2, 1 );
    Scheduler *sched = new Scheduler();
    Simulator<AbstractNode *> *sim = new Simulator<AbstractNode *>( 1, taskc->get_hyperperiod(), taskc, sched, true, false );

    sim->set_heuristic( heuristic );
    std::vector<double> utils;
    std::vector<double> results;

    std::vector<Task *> test_tasks;

    for( size_t i=0; i<=14; i++ ) {
        utils.push_back( 0.90 + i * 0.05 );
    }

    std::vector<double> mean_qos;
    std::vector<double> actual_utils;

    for( size_t i=0; i<utils.size(); i++ ) {
        taskc->set_overload(utils[i]);
        taskc->set_task_number(6);
        for (size_t j = 0; j < 100; j++) {
            do {
                taskc->create_test_set(test_tasks);
                taskc->compute_hyperperiod( test_tasks );
            } while( taskc->get_hyperperiod() > 10000 );
            double tmp_util = 0;
            for( auto & element : test_tasks ) {
                tmp_util += static_cast<double>( element->get_duration() ) / static_cast<double>( element->get_period() ) ;
            }
            actual_utils.push_back( tmp_util );
            sim->set_pending(test_tasks);
            sim->set_finish_time(taskc->get_hyperperiod());
            sim->run();
            mean_qos.push_back( sim->get_qos() );
        }
    }

    generate_csv( mean_qos, actual_utils, "singleheur_qos.csv" );
}

void test_utils_wCPU( AbstractNode * heuristic )
{
    UunifastCreator *taskc = new UunifastCreator( 3, "./../../test_inputs/test_1.txt", true, 20, 4, 2, 1 );
    Scheduler *sched = new Scheduler();
    Simulator<AbstractNode *> *sim = new Simulator<AbstractNode *>( 1, taskc->get_hyperperiod(), taskc, sched, true, false );

    sim->set_heuristic( heuristic );
    std::vector<double> utils;
    std::vector<double> results;

    std::vector<Task *> test_tasks;

    for( size_t i=0; i<=14; i++ ) {
        utils.push_back( 0.90 + i * 0.05 );
    }

    std::vector<double> mean_qos;
    std::vector<double> actual_utils;

    for( size_t i=0; i<utils.size(); i++ ) {
        taskc->set_overload(utils[i]);
        taskc->set_task_number(6);
//        double sum = 0;
        for (size_t j = 0; j < 100; j++) {
            do {
                taskc->create_test_set(test_tasks);
                taskc->compute_hyperperiod( test_tasks );
            } while( taskc->get_hyperperiod() > 10000 );
            double tmp_util = 0;
            for( auto & element : test_tasks ) {
                tmp_util += static_cast<double>( element->get_duration() ) / static_cast<double>( element->get_period() ) ;
            }
            actual_utils.push_back( tmp_util );
            sim->set_pending(test_tasks);
            sim->set_finish_time(taskc->get_hyperperiod());
            sim->run();
            mean_qos.push_back( sim->get_time_wasted() / taskc->get_hyperperiod() );
        }
    }

    generate_csv( mean_qos, actual_utils, "singleheur_qos.csv" );
}

void pareto_test( AbstractNode * heuristic )
{
    UunifastCreator *taskc = new UunifastCreator( 3, "./../../test_inputs/test_1.txt", true, 20, 4, 2, 1 );
    Scheduler *sched = new Scheduler();
    Simulator<AbstractNode *> *sim = new Simulator<AbstractNode *>( 1, taskc->get_hyperperiod(), taskc, sched, true, false );

    sim->set_heuristic( heuristic );
    std::vector<double> utils;
    std::vector<double> results;

    std::vector<Task *> test_tasks;

    for( size_t i=0; i<=14; i++ ) {
        utils.push_back( 0.90 + i * 0.05 );
    }

    std::vector<double> gini;
    std::vector<double> skip;

    for( size_t i=0; i<utils.size(); i++ ) {
        taskc->set_overload(utils[i]);
        taskc->set_task_number(6);
//        double sum = 0;
        for (size_t j = 0; j < 100; j++) {
            do {
                taskc->create_test_set(test_tasks);
                taskc->compute_hyperperiod( test_tasks );
            } while( taskc->get_hyperperiod() > 10000 );
            double tmp_util = 0;
            for( auto & element : test_tasks ) {
                tmp_util += static_cast<double>( element->get_duration() ) / static_cast<double>( element->get_period() ) ;
            }
            if( tmp_util >= 0.9 && tmp_util <= 1.60 ) {
                sim->set_pending(test_tasks);
                sim->set_finish_time(taskc->get_hyperperiod());
                sim->run();
                sim->compute_mean_skip_factor();
                skip.push_back( sim->compute_skip_fitness() );
                gini.push_back( sim->compute_gini_coeff() );
            }
        }
    }
    generate_csv( gini, skip, "pareto_single.csv" );
}