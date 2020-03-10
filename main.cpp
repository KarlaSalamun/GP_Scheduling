#include "TreeConstructor.h"
#include "TreeSolution.h"
#include "EvaluateHeuristic.h"
#include "GeneticAlgorithm.h"
#include "TreeMutation.h"
#include "TreeSelection.h"
#include "TreeCrossover.h"
#include "TreeMutation.cpp"
#include "TreeCrossover.cpp"
#include "TreeSelection.cpp"
#include "TreeSolution.cpp"
#include "GeneticAlgorithm.cpp"

int main( void )
{
    srand(static_cast<double> (0));
    //srand(static_cast<double> (time(NULL)) );

    TreeConstructor *tc = new TreeConstructor();
    TreeSolution<AbstractNode *> solution;

    int population_size = 100;
    int generation_number = 300;

    TreeSolution<AbstractNode *>result;

    std::vector<TreeSolution<AbstractNode *>>population( population_size );
    for( int i=0; i<population_size; i++ ) {
        tc->construct_tree_full( 3, population[i].data );
    }

    tc->draw_tree( population[0].data, "first.dot" );

    tc->construct_tree_full( 5, solution.data );

    EvaluateHeuristic *evaluator = new EvaluateHeuristic();

    TreeMutation<TreeSolution<AbstractNode *>> *mutation = new TreeMutation<TreeSolution<AbstractNode *>>();
    TreeSelection<TreeSolution<AbstractNode *>> *selection = new TreeSelection<TreeSolution<AbstractNode *>>();
    TreeCrossover<TreeSolution<AbstractNode *>> *crossover = new TreeCrossover<TreeSolution<AbstractNode *>>();

    EvaluateHeuristic *test_function = new EvaluateHeuristic();

    GeneticAlgorithm<TreeSolution<AbstractNode *>> *ga = new GeneticAlgorithm<TreeSolution<AbstractNode *>>( crossover,
            mutation, selection, test_function, generation_number, population_size, 0 );

    ga->get_solution( population, result );

    tc->draw_tree( result.data, "after.dot" );

    return 0;
}