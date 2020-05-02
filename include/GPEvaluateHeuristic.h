//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_GPEVALUATEHEURISTIC_H
#define GP_SCHEDULING_GPEVALUATEHEURISTIC_H

#include <utility>
#include <vector>
#include <queue>
#include "TreeSolution.h"
#include "Nodes/AbstractNode.h"
#include "../function.h"
#include "UunifastCreator.h"
#include "Simulator.h"

class GPEvaluateHeuristic : public Function<TreeSolution<AbstractNode *>> {
    public:
        explicit GPEvaluateHeuristic( int task_number ) : task_number( task_number ) {}
        GPEvaluateHeuristic() {}
        virtual ~GPEvaluateHeuristic() {
            for( auto & element : test_tasks ) {
                delete element;
            }
            for( auto & element : pending_tasks ) {
                delete element;
            }
            for( auto & element : processed_tasks ) {
                delete element;
            }
        }
        double get_value( TreeSolution<AbstractNode *> &solution ) override;
        void get_value_NSGA( TreeSolution<AbstractNode *>&, std::pair<double, double>&, bool ) override {};
        void set_test_tasks( std::vector<Task *> tasks ) {
            test_tasks = tasks;
        }
        bool periodic;
    protected:
        int task_number;
        std::vector<Task *> test_tasks;
        std::vector<Task *> pending_tasks;
        std::vector<Task *> processed_tasks;
        static int compare_priority( const void *t1, const void *t2 );
};

#endif //GP_SCHEDULING_GPEVALUATEHEURISTIC_H
