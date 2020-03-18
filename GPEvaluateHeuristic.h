//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_GPEVALUATEHEURISTIC_H
#define GP_SCHEDULING_GPEVALUATEHEURISTIC_H

#include <utility>
#include <vector>
#include <queue>
#include "Task.h"
#include "TaskCreator.h"
#include "TreeSolution.h"
#include "Nodes/AbstractNode.h"
#include "../function.h"

class GPEvaluateHeuristic : public Function<TreeSolution<AbstractNode *>> {
    public:
        explicit GPEvaluateHeuristic( std::vector<Task *> test_tasks ) : test_tasks(std::move( test_tasks )) {}
        GPEvaluateHeuristic() {}
        double get_value( TreeSolution<AbstractNode *> &solution ) override;
        void set_test_tasks( std::vector<Task *> tasks ) {
            test_tasks = tasks;
        }
    private:
        std::vector<Task *> test_tasks;
        std::vector<Task *> pending_tasks;
        std::vector<Task *> processed_tasks;
        static int compare_priority( const void *t1, const void *t2 );
};

#endif //GP_SCHEDULING_GPEVALUATEHEURISTIC_H
