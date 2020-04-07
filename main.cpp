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

namespace plt = matplotlibcpp;

void generate_csv( std::vector<double> results );

int main( void )
{
    TreeSolution<AbstractNode *>result;
//    srand(static_cast<double> (0));
    srand(static_cast<double> (time(NULL)) );

    TreeConstructor *tc = new TreeConstructor();

    int population_size = 100;
    // TODO stavi ovo u funkciju
    std::vector<TreeSolution<AbstractNode *>> population( population_size );
    for( int i=0; i<population_size; i++ ) {
        tc->construct_tree_grow( 4, population[i].data );
    }

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    GPEvaluateHeuristic *test_function = new GPEvaluateHeuristic( 20 );
    test_function->periodic = true;

    GPEvaluateHeuristic *train_function = new GPEvaluateHeuristic( 10 );
    train_function->periodic = true;

    tc->draw_tree( population[0].data, "prije.dot" );

    GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
            mutation, selection, test_function, train_function, 50, population_size, 0 );

    ga->get_solution( population, result );

    tc->draw_tree( result.data, "poslije.dot" );

    std::vector<double> train_solutions;

    ga->get_train_solutions( train_solutions );
    plt::plot( train_solutions );
    plt::show();
    generate_csv( train_solutions );

   return 0;
}

void run_evaluations( GeneticAlgorithm<TreeSolution<AbstractNode *>> , int eval_num, int testset_size )
{
    for( int i=0; i<eval_num; i++ ) {
        GPEvaluateHeuristic *test_function = new GPEvaluateHeuristic( testset_size );
        test_function->periodic = true;
    }
}

void generate_csv( std::vector<double> results )
{
    FILE *fd = fopen( "../test_results.csv", "w+" );
    for( size_t i=0; i<results.size(); i++ ) {
        fprintf( fd, "%zu,%lf\n", i+1, results[i] );
    }
    fclose( fd );
}
