//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_EVALUATEHEURISTIC_H
#define GP_SCHEDULING_EVALUATEHEURISTIC_H

#include <vector>
#include <queue>
#include "Task.h"
#include "../function.h"

class EvaluateHeuristic : public Function<TreeSolution<AbstractNode *>> {
    public:
        EvaluateHeuristic( std::vector<Task> pending_tasks ) : pending_tasks( pending_tasks ) {}
        double get_value( TreeSolution<AbstractNode *> &solution ) override;
        void generate_tasks( int tasks_num );
        std::vector<Task> pending_tasks;
    private:
        std::vector<Task> processed_tasks;
};


#endif //GP_SCHEDULING_EVALUATEHEURISTIC_H
