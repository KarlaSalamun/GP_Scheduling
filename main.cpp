#include <memory>
#include "TreeConstructor.h"
#include "TreeSolution.h"
#include "GPEvaluateHeuristic.h"
#include "GeneticAlgorithm.h"
#include "TreeMutation.h"
#include "TreeSelection.h"
#include "TreeCrossover.h"
#include "TreeMutation.cpp"
#include "TreeCrossover.cpp"
#include "TreeSelection.cpp"
#include "TreeSolution.cpp"
#include "GeneticAlgorithm.cpp"
#include "GPEvaluateHeuristic.cpp"
#include "Heuristics/EvaluateHeuristic.h"
#include "Heuristics/RMHeuristic.h"
#include "Heuristics/MONHeuristic.h"
#include "Heuristics/WSPTHeuristic.h"
#include "Heuristics/EDDHeuristic.h"
#include "Heuristics/HODGHeuristic.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void test_generations( int max_generations );
void test_populations();
void test_tree_depth();
void test_set_size();
void generate_csv( std::vector<double> results );

int main( void )
{
//    srand(static_cast<double> (0));
    srand(static_cast<double> (time(NULL)) );
    test_generations(50);

//    TreeConstructor *tc = new TreeConstructor();
//
//    TreeSolution<AbstractNode *> solution;
//
//    std::vector<Task_p *>test_tasks;
//    std::vector<Task_p *>train_tasks;
//
//    TreeSolution<AbstractNode *>result;
//
//    TaskCreator *task_creator = new TaskCreator();
//    task_creator->periodic = true;
//    task_creator->set_task_number( 10 );
//    task_creator->create_periodic_test_set( test_tasks );
//    task_creator->create_periodic_test_set( train_tasks );
//
//    task_creator->write_tasks_p( test_tasks );
//
//    int population_size = 10;
//    std::vector<TreeSolution<AbstractNode *>> population( population_size );
//    for( int i=0; i<population_size; i++ ) {
//        tc->construct_tree_grow( 4, population[i].data );
//    }
//
//    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
//    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
//    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();
//
//    GPEvaluateHeuristic<Task_p *> *test_function = new GPEvaluateHeuristic<Task_p *>( test_tasks );
//    test_function->set_test_tasks( test_tasks );
//    test_function->periodic = true;
//
//    GPEvaluateHeuristic<Task_p *> *train_function = new GPEvaluateHeuristic<Task_p *>( train_tasks );
//    train_function->set_test_tasks( train_tasks );
//    train_function->periodic = true;
//
//    GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
//            mutation, selection, test_function, train_function, 50, population_size, 0 );
//
//    ga->get_solution( population, result );

//    test_generations( 50 );
//        test_populations();
//    test_tree_depth();
    //test_set_size();
//    std::vector<double> train_results(10);
//    std::vector<double> test_results(10);
//    std::vector<double> generations;

//    for( int i=0; i<10; i++ ) {
//
//        generation_number = ( i + 1 ) * 10;
//        generations.push_back(static_cast<double> ( generation_number ) );
//        std::vector<TreeSolution<AbstractNode *>>tmp_population( population_size );
//        tmp_population = population;
//
//        std::unique_ptr<GeneticAlgorithm<TreeSolution<AbstractNode *>>> ga =
//                std::make_unique<GeneticAlgorithm<TreeSolution<AbstractNode *>>>(
//                        crossover, mutation, selection, train_function, generation_number, population_size, 0 );
//        ga->get_solution( tmp_population, result );
//        train_results[i] = train_function->get_value( result );
//        test_results[i] = test_function->get_value( result );
//    }

//    plt::named_plot( "train set", generations, train_results );
//    plt::named_plot( "test set", generations, test_results );
//    plt::legend();
//    plt::save("./1000_generations.png");
//    plt::show();


//    tc->draw_tree( result.data, "after.dot" );



//   RMHeuristic *rm = new RMHeuristic();
//   evaluator->heuristic = rm;
//   double twt_rm = evaluator->calculate_twt();
//
//   MONHeuristic *mon = new MONHeuristic();
//   evaluator->heuristic = mon;
//   double twt_mon = evaluator->calculate_twt();
//
//   WSPTHeuristic *wspt = new WSPTHeuristic();
//   evaluator->heuristic = wspt;
//   double twt_wspt = evaluator->calculate_twt();

//   std::vector<double> solutions;
//   ga->get_best_solutions( solutions );


//
//   plt::plot( solutions );
//   plt::show();

//   double twt_gp = test_function->get_value( result );
//
//    GPEvaluateHeuristic *test_function2 = new GPEvaluateHeuristic();
//    test_function2->set_test_tasks( train_tasks );
//
//    double twt_2 = test_function2->get_value( result );
//
//   printf( "GP heuristika\ttwt = %lf\n", twt_gp );
//   printf( "drugi set:\ttwt = %lf\n", twt_2 );
//   printf("RM heuristika\ttwt = %lf\n", twt_rm );
//   printf( "MON heuristika\ttwt = %lf\n", twt_mon );
//   printf( "WSPT heuristika\ttwt = %lf\n", twt_wspt );

   return 0;
}

void test_generations( int max_generations )
{
    TreeConstructor *tc = new TreeConstructor();

    TreeSolution<AbstractNode *>result;

    std::vector<Task_p *>test_tasks;
    std::vector<Task_p *>train_tasks;

    TaskCreator *task_creator = new TaskCreator( 10, 0.6, 0.6 );
    task_creator->create_periodic_test_set( test_tasks );
    task_creator->create_periodic_test_set( train_tasks );
//    task_creator->load_tasks( train_tasks );

    int population_size = 10;
    std::vector<TreeSolution<AbstractNode *>> population( population_size );
    for( int i=0; i<population_size; i++ ) {
        tc->construct_tree_grow( 4, population[i].data );
    }

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    GPEvaluateHeuristic<Task_p *> *test_function = new GPEvaluateHeuristic<Task_p *>( test_tasks );
    test_function->periodic = true;
    test_function->set_test_tasks(test_tasks);

    GPEvaluateHeuristic<Task_p *> *train_function = new GPEvaluateHeuristic<Task_p *>( train_tasks );
    train_function->periodic = true;
    train_function->set_test_tasks(train_tasks);
    task_creator->write_tasks_p( train_tasks );

    GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
            mutation, selection, test_function, train_function, max_generations, population_size, 0 );

    std::vector<double> train_solutions;

    for( int i=0; i<1; i++ ) {
        for( int i=0; i<population_size; i++ ) {
            tc->construct_tree_grow( 5, population[i].data );
        }
        ga->get_solution( population, result );
        ga->get_train_solutions( train_solutions );
//        train_solutions.push_back( result.fitness );
    }

//    ga->get_solution( population, result );


//    std::vector<double> test_solutions;

    generate_csv( train_solutions );

//    ga->get_train_solutions( train_solutions );
//    ga->get_test_solutions( test_solutions );

//    plt::named_plot( "train set", train_solutions );
//    plt::named_plot( "test set", test_solutions );
//    plt::legend();
//    plt::show();
}

void test_populations()
{
    vector<int> population_size{ 10, 20, 50, 100 };
//    vector<int> population_size{ 10, 20 };

    TreeConstructor *tc = new TreeConstructor();

    TreeSolution<AbstractNode *>result;

    std::vector<Task *> test_tasks;
    std::vector<Task *> train_tasks;

    std::vector<double> test_results;
    std::vector<double> train_results;

    TaskCreator *task_creator = new TaskCreator( 12, 0.6, 0.6 );
    task_creator->create_test_set(test_tasks );
    task_creator->create_test_set( train_tasks );

    int generation_number = 50;

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    GPEvaluateHeuristic<Task *> *test_function = new GPEvaluateHeuristic<Task *>( test_tasks );
    GPEvaluateHeuristic<Task *> *train_function = new GPEvaluateHeuristic<Task *>( train_tasks );


    for( auto & size : population_size ) {

        std::vector<TreeSolution<AbstractNode *>> population( size );

        for( int i=0; i<population.size(); i++ ) {
            tc->construct_tree_grow( 5, population[i].data );
        }

        GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
                mutation, selection, test_function, train_function, generation_number, size, 0 );

        ga->get_solution( population, result );
/*
        train_results.push_back( train_function->get_value( result ) );
        test_results.push_back( test_function->get_value( result ) );
*/
        delete ga;
    }

//    plt::plot( population_size, train_results );

        std::vector<double> x( population_size.begin(), population_size.end() );

        plt::named_plot( "train set", x, train_results );
        plt::named_plot( "test set", x, test_results );
        plt::legend();
    plt::show();
}

void test_tree_depth()
{
    vector<int> tree_depth{ 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20 };
//    vector<int> tree_depth{ 3, 5, 8 };

    TreeConstructor *tc = new TreeConstructor();

    TreeSolution<AbstractNode *>result;

    std::vector<Task *>test_tasks;
    std::vector<Task *>train_tasks;

    std::vector<double> test_results;
    std::vector<double> train_results;

    TaskCreator *task_creator = new TaskCreator( 12, 0.6, 0.6 );
    task_creator->create_test_set( test_tasks );
    task_creator->create_test_set( train_tasks );

    int generation_number = 50;
    int population_size = 10;

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    GPEvaluateHeuristic<Task *> *test_function = new GPEvaluateHeuristic<Task *>( test_tasks );
    GPEvaluateHeuristic<Task *> *train_function = new GPEvaluateHeuristic<Task *>( train_tasks );

    for( auto & depth : tree_depth ) {

        std::vector<TreeSolution<AbstractNode *>> population( population_size );

        for( int i=0; i<population.size(); i++ ) {
            tc->construct_tree_grow( depth, population[i].data );
        }

        crossover->set_depth( depth );
        mutation->set_depth( depth );

        GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
                mutation, selection, test_function, train_function, generation_number, population_size, 0 );

        ga->get_solution( population, result );

        train_results.push_back( train_function->get_value( result ) );
        test_results.push_back( test_function->get_value( result ) );

        delete ga;
    }

//    plt::plot( population_size, train_results );

    std::vector<double> x( tree_depth.begin(), tree_depth.end() );

    plt::named_plot( "train set", x, train_results );
    plt::named_plot( "test set", x, test_results );
    plt::legend();
    plt::show();
}

void test_set_size()
{
    vector<int> set_size{ 12, 25, 50, 100 };
//    vector<int> tree_depth{ 3, 5, 8 };

    TreeConstructor *tc = new TreeConstructor();

    TreeSolution<AbstractNode *>result;

    std::vector<Task *>test_tasks;
    std::vector<Task *>train_tasks;

    std::vector<double> test_results;
    std::vector<double> train_results;



    int generation_number = 50;

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    TaskCreator *task_creator2 = new TaskCreator( 12, 0.6, 0.6 );

    task_creator2->create_test_set( test_tasks );
    GPEvaluateHeuristic <Task *> *test_function = new GPEvaluateHeuristic<Task *>( test_tasks );


    for( auto & size : set_size ) {

        std::vector<TreeSolution<AbstractNode *>> population( 10 );

        for( int i=0; i<population.size(); i++ ) {
            tc->construct_tree_grow( 5, population[i].data );
        }

        TaskCreator *task_creator1 = new TaskCreator( size, 0.6, 0.6 );
        task_creator1->create_test_set( train_tasks );

        GPEvaluateHeuristic<Task *> *train_function = new GPEvaluateHeuristic<Task *>( train_tasks );

        GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
                mutation, selection, test_function, train_function, generation_number, population.size(), 0 );

        ga->get_solution( population, result );
        test_results.push_back( test_function->get_value( result ) );
    }

//    plt::plot( population_size, train_results );

    std::vector<double> x( set_size.begin(), set_size.end() );

    plt::named_plot( "test set", x, test_results );
    plt::legend();
    plt::show();
}

void generate_csv( std::vector<double> results )
{
    FILE *fd = fopen( "../test_results.csv", "w+" );
    for( int i=0; i<results.size(); i++ ) {
        fprintf( fd, "%d,%lf\n", i+1, results[i] );
    }
    fclose( fd );
}