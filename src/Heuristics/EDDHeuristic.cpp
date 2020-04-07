//
// Created by karla on 11. 03. 2020..
//

#include "EDDHeuristic.h"

double EDDHeuristic::calculate_priority(Task *&task, std::vector<Task *> )
{
    return 1. / task->get_abs_due_date();
}