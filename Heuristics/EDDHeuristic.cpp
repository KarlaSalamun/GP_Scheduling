//
// Created by karla on 11. 03. 2020..
//

#include "EDDHeuristic.h"

double EDDHeuristic::calculate_priority(Task *&task, std::vector<Task *> pending_tasks)
{
    return 1. / task->due_date;
}