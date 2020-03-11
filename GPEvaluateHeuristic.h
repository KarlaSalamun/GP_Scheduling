//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_GPEVALUATEHEURISTIC_H
#define GP_SCHEDULING_GPEVALUATEHEURISTIC_H

#include <vector>
#include <queue>
#include "Task.h"
#include "TaskCreator.h"
#include "TreeSolution.h"
#include "Nodes/AbstractNode.h"
#include "../function.h"

class GPEvaluateHeuristic : public Function<TreeSolution<AbstractNode *>> {
    public:
        GPEvaluateHeuristic() {}
        double get_value( TreeSolution<AbstractNode *> &solution ) override;
        std::vector<Task *> pending_tasks;
    private:
        std::vector<Task *> processed_tasks;
        static int compare_priority( const void *t1, const void *t2 );
};


#endif //GP_SCHEDULING_GPEVALUATEHEURISTIC_H
