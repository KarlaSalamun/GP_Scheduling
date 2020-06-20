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
void test_utils_wCPU( std::pair<AbstractNode *, AbstractNode *> heuristic );
void test_utils_qos( std::pair<AbstractNode *, AbstractNode *> heuristic );


int main( void )
{
    TreeSolution<AbstractNode *>result;
//    srand(static_cast<double> (0));
    srand(static_cast<double> (time(NULL)) );

    TreeConstructor *tc = new TreeConstructor();

    int population_size = 10;
    TreePopulation<TreeSolution<AbstractNode *>> *tp =
            new TreePopulation<TreeSolution<AbstractNode *>>( population_size, tc );
    // TODO stavi ovo u funkciju
    std::vector<TreeSolution<AbstractNode *>> population;
    tp->create_new_population( population );

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    GPEvaluate_NSGA *nsga = new GPEvaluate_NSGA( 3 );
    nsga->initialize();
    GPEvaluate_NSGA *nsga1 = new GPEvaluate_NSGA( 3 );
    nsga1->initialize();

//    GPEvaluateHeuristic *testf = new GPEvaluateHeuristic( 4 );
//    GPEvaluateHeuristic *trainf = new GPEvaluateHeuristic( 4 );

    std::vector<double> wasted;

    auto *ga = new NSGA<TreeSolution<AbstractNode *>>( crossover,
            mutation, selection, nsga, nsga1, tp, 50, population_size, 0 );
    ga->get_solution( population, result );
//
//    UunifastCreator *taskc = new UunifastCreator( 3, "./../../test_inputs/test_1.txt", true, 20, 4, 2, 1 );
//    Scheduler *sched = new Scheduler();
//    Simulator<AbstractNode *> *sim = new Simulator<AbstractNode *>( 1, taskc->get_hyperperiod(), taskc, sched, true, false );
//
//    sim->set_heuristic( result.data );
//    std::vector<double> utils;
//    std::vector<double > generations;
//
//    generations.push_back( 1. );
//
//    std::vector<Task *> test_tasks;
//
//    for( size_t i=0; i<=14; i++ ) {
//        utils.push_back( 0.90 + i * 0.05 );
//    }
//
//    std::vector<double> actual_utils;
//    double total_wasted = 0;
//
//    for( size_t i=0; i<utils.size(); i++ ) {
//        taskc->set_overload(utils[i]);
//        taskc->set_task_number(6);
////        double sum = 0;
//        for (size_t j = 0; j < 20; j++) {
//            do {
//                taskc->create_test_set(test_tasks);
//                taskc->compute_hyperperiod( test_tasks );
//            } while( taskc->get_hyperperiod() > 10000 );
//            sim->set_pending(test_tasks);
//            sim->set_finish_time(taskc->get_hyperperiod());
//            sim->run();
//            total_wasted+=sim->get_time_wasted() / taskc->get_hyperperiod();
//            for( auto & element : test_tasks ) {
//                delete element;
//            }
//        }
//    }
//    wasted.push_back( total_wasted / 20 );


//    for( size_t i=5; i<= 50; i=i+5 ) {
//        population.clear();
//        total_wasted = 0;
//        generations.push_back( static_cast<double>( i ) );
//        ga->set_generation_num( i );
//        tp->create_new_population( population );
//        ga->get_solution( population, result );
//        nsga->initialize();
//        nsga1->initialize();
//
//        sim->set_heuristic( result.data );
//
////        for( size_t j=0; j<utils.size(); j++ ) {
////            taskc->set_overload(utils[j]);
////            taskc->set_task_number(6);
////        double sum = 0;
//            for (size_t k = 0; k < 20; k++) {
//                do {
//                    taskc->set_overload( 1.2 );
//                    taskc->create_test_set(test_tasks);
//                    taskc->compute_hyperperiod( test_tasks );
//                } while( taskc->get_hyperperiod() > 10000 );
//                sim->set_pending(test_tasks);
//                sim->set_finish_time(taskc->get_hyperperiod());
//                sim->run();
//                total_wasted+=sim->get_time_wasted() / taskc->get_hyperperiod();
//                for( auto & element : test_tasks ) {
//                    delete element;
//                }
//            }
////        }
//        wasted.push_back( total_wasted / 20 );
//    }
//
//    generate_csv( wasted, generations, "coev_gens.csv" );

    test_utils_wCPU( result.data );
//    test_utils_qos( result.data );

    delete ga;
//    std::vector<Task *> pending;
//
//    UunifastCreator *taskc = new UunifastCreator( 3, "./../../test_inputs/test_1.txt", true, 100, 10, 10, 1 );
//    taskc->set_time_slice( 1 );
//    taskc->load_tasks( pending );
//
//    std::vector<double> durations;
//    for( auto & element : pending ) {
//        durations.push_back( element->get_duration() );
//        element->initialize_task();
//        assert( element->get_duration() != 0 );
//    }
//
//    Scheduler *sched = new Scheduler();
//    taskc->compute_hyperperiod( pending );
//    Simulator<AbstractNode *> *sim = new Simulator<AbstractNode *>( 1, taskc->get_hyperperiod(), taskc, sched, true, true );


//    sim->set_heuristic( result.data );
//    sim->set_finish_time( taskc->get_hyperperiod() );
//    sim->set_display();
//    sim->set_filename( "./../../test_outputs/comparison.tex" );
//    sim->set_pending( pending );
//    sim->run();
//
//    taskc->set_filename("./../../test_inputs/test_1.txt");
//    taskc->set_task_number(3);
//    taskc->load_tasks( pending );
//    for( auto & element : pending ) {
//        element->initialize_task();
//    }
//    sim->set_finish_time( taskc->get_hyperperiod() );
//    sim->set_pending( pending );
//    sim->run();
//
//    taskc->set_filename("./../../test_inputs/test_2.txt");
//    taskc->set_task_number(2);
//    taskc->load_tasks( pending );
//    for( auto & element : pending ) {
//        element->initialize_task();
//    }
//    sim->set_finish_time( taskc->get_hyperperiod() );
//    sim->set_pending( pending );
//    sim->run();
//
//    taskc->set_filename("./../../test_inputs/test_3.txt");
//    taskc->set_task_number(3);
//    taskc->load_tasks( pending );
//    for( auto & element : pending ) {
//        element->initialize_task();
//    }
//    sim->set_finish_time( taskc->get_hyperperiod() );
//    sim->set_pending( pending );
//    sim->run();
//
//    std::vector<double> utils;
//    std::vector<double> results;
//
//    for( int overload = 90; overload <= 160; overload = overload + 5 ) {
//        std::string tmp = "./../../test_inputs/" + std::to_string( overload ) + ".txt";
//        taskc->set_filename( tmp );
//        taskc->load_tasks( pending );
////        overload_values.push_back( overload );
//        double util = 0;
////        taskc->set_overload( overload );
////        taskc->compute_overloaded( pending, durations );
//        for( auto & element : pending ) {
//            element->initialize_task();
//            util += element->get_duration() / element->get_period();
//        }
//        printf( "%f\n", util );
//        sim->set_finish_time( taskc->get_hyperperiod() );
//        sim->set_pending( pending );
//        sim->run();
//        sim->compute_mean_skip_factor();
//        printf( "overload: %d\twasted time: %lf\tmean skip factor: %lf\n", overload, sim->get_time_wasted(), sim->get_mean_skip_factor() );
//        utils.push_back( overload / 100. );
//        results.push_back( sim->get_time_wasted() );
//    }
//
//    generate_csv( results, utils, "coevolution_wt.csv" );
    /*
    GPEvaluateHeuristic *test_function = new GPEvaluateHeuristic( 4 );
    test_function->periodic = true;

    GPEvaluateHeuristic *train_function = new GPEvaluateHeuristic( 4 );
    train_function->periodic = true;

    tc->draw_tree( population[0].data, "./../../tree_graphs/my_tree_graphs/prije.dot" );

    GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
            mutation, selection, test_function, train_function, 50, population_size, 0 );

    ga->get_solution( population, result );

    tc->draw_tree( result.data, "./../../tree_graphs/my_tree_graphs/poslije.dot" );

    std::vector<double> train_solutions;

    ga->get_train_solutions( train_solutions );
    plt::plot( train_solutions );
    plt::show();
    generate_csv( train_solutions );
     */
    tc->draw_tree( result.data.first, "../graphs/skipfactoropt.dot" );
   return 0;
}

//void run_evaluations( GeneticAlgorithm<TreeSolution<AbstractNode *>> , int eval_num, int testset_size )
//{
////    for( int i=0; i<eval_num; i++ ) {
////        GPEvaluateHeuristic *test_function = new GPEvaluateHeuristic( testset_size );
////        test_function->periodic = true;
////    }
//}

void generate_csv(std::vector<double> results, std::vector<double> utils, std::string filename )
{
    std::string tmp = "./../../test_outputs/";
    FILE *fd = fopen( (tmp + filename).c_str(), "w+" );
    for( size_t i=0; i<results.size(); i++ ) {
        fprintf( fd, "%lf,%lf\n", utils[i], results[i] );
    }
    fclose( fd );
}

void test_utils_wCPU( std::pair<AbstractNode *, AbstractNode *> heuristic )
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
            assert( sim->get_qos() >= 0.01 );
            assert( sim->get_time_wasted() >= 0 );
            for( auto & element : test_tasks ) {
                delete element;
            }
        }
    }

    generate_csv( mean_qos, actual_utils, "coev_wCPU.csv" );
    delete sim;
    delete sched;
    delete taskc;
}

void test_utils_qos( std::pair<AbstractNode *, AbstractNode *> heuristic )
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
            mean_qos.push_back( sim->get_qos() );
            for( auto & element : test_tasks ) {
                delete element;
            }
        }
    }

    generate_csv( mean_qos, actual_utils, "coev_qos.csv" );
    delete sim;
    delete sched;
    delete taskc;
}