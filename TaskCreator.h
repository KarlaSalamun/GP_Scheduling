//
// Created by karla on 09. 03. 2020..
//

#ifndef GP_SCHEDULING_TASKCREATOR_H
#define GP_SCHEDULING_TASKCREATOR_H

#include <vector>
#include "Task.h"

class TaskCreator {
    public:
        TaskCreator( int task_number, double dd_range, double dd_tightness ) :
            task_number( task_number ), dd_range( dd_range ), dd_tightness( dd_tightness ) {}

        TaskCreator() {}

        void set_task_number( int task_number )
        {
            task_number = task_number;
        }
        void set_dd_range( double dd_range )
        {
            dd_range = dd_range;
        }
        void set_dd_tightness( double dd_tightness )
        {
            dd_tightness = dd_tightness;
        }

        void create_test_set( std::vector<Task *> &test_tasks );
        int task_number;
        double dd_range;
        double dd_tightness;
};


#endif //GP_SCHEDULING_TASKCREATOR_H
