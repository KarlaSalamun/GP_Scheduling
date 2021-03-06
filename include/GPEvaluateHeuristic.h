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

class GPEvaluateHeuristic : public Function<TreeSolution<AbstractNode *>> {
    public:
        explicit GPEvaluateHeuristic( int task_number ) : task_number( task_number ) {}
        GPEvaluateHeuristic() {}
        double get_value( TreeSolution<AbstractNode *> &solution ) override;
        void set_test_tasks( std::vector<Task *> tasks ) {
            test_tasks = tasks;
        }
        bool periodic;
        std::pair<double, double> get_value_NSGA( TreeSolution<AbstractNode *> & ) override {
            return std::make_pair( 0, 0 );
        }

protected:
        int task_number;
        std::vector<Task *> test_tasks;
        std::vector<Task *> pending_tasks;
        std::vector<Task *> processed_tasks;
        static int compare_priority( const void *t1, const void *t2 );
};

#endif //GP_SCHEDULING_GPEVALUATEHEURISTIC_H
