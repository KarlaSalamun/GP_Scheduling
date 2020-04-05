//
// Created by karla on 10. 03. 2020..
//

#include "WSPTHeuristic.h"

double WSPTHeuristic::calculate_priority( Task *&task, std::vector<Task *> )
{
    return task->get_weight() / task->get_duration();
}