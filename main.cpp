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
#include "Heuristics/EvaluateHeuristic.h"
#include "Heuristics/RMHeuristic.h"
#include "Heuristics/MONHeuristic.h"
#include "Heuristics/WSPTHeuristic.h"

int main( void )
{
    srand(static_cast<double> (0));
    //srand(static_cast<double> (time(NULL)) );

    TreeConstructor *tc = new TreeConstructor();
    TreeSolution<AbstractNode *> solution;

    int population_size = 10;
    int generation_number = 10;

    TreeSolution<AbstractNode *>result;

    std::vector<TreeSolution<AbstractNode *>>population( population_size );
    for( int i=0; i<population_size; i++ ) {
        tc->construct_tree_grow( 5, population[i].data );
    }

    tc->draw_tree( population[0].data, "first.dot" );

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    GPEvaluateHeuristic *test_function = new GPEvaluateHeuristic();

    GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
            mutation, selection, test_function, generation_number, population_size, 0 );

    ga->get_solution( population, result );

    tc->draw_tree( result.data, "after.dot" );

    EvaluateHeuristic *evaluator = new EvaluateHeuristic();

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
//
//   GPEvaluateHeuristic *gp = new GPEvaluateHeuristic();
//   double twt_gp = gp->get_value( result );

//   printf( "GP heuristika\ttwt = %lf\n", twt_gp );
//   printf("RM heuristika\ttwt = %lf\n", twt_rm );
//   printf( "MON heuristika\ttwt = %lf\n", twt_mon );
//   printf( "WSPT heuristika\ttwt = %lf\n", twt_wspt );

    return 0;
}