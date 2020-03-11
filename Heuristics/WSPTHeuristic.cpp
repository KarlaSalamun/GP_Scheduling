//
// Created by karla on 10. 03. 2020..
//

#include "WSPTHeuristic.h"

double WSPTHeuristic::calculate_priority( Task *&task, std::vector<Task *> pending_tasks )
{
    return task->weight / task->duration;
}