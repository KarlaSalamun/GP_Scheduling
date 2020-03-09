#include "TreeConstructor.h"
#include "TreeSolution.h"
#include "EvaluateHeuristic.h"

int main( void )
{
    TreeConstructor *tc = new TreeConstructor();
    TreeSolution<AbstractNode *> solution;
    tc->construct_tree_full( 5, solution.data );
    tc->draw_tree( solution.data, "first_test.dot" );

    return 0;
}