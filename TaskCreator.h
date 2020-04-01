//
// Created by karla on 09. 03. 2020..
//

#ifndef GP_SCHEDULING_TASKCREATOR_H
#define GP_SCHEDULING_TASKCREATOR_H

#include <vector>
#include "Task.h"
#include "Task_p.h"

class TaskCreator {
    public:
        TaskCreator( int task_number, double dd_range, double dd_tightness ) :
            task_number( task_number ), dd_range( dd_range ), dd_tightness( dd_tightness ) {
            periodic = false;
        }

        TaskCreator() {}

        void set_task_number( int task_number )
        {
            this->task_number = task_number;
        }
        void set_dd_range( double dd_range )
        {
            this->dd_range = dd_range;
        }
        void set_dd_tightness( double dd_tightness )
        {
            this->dd_tightness = dd_tightness;
        }

        void create_test_set( std::vector<Task *> &test_tasks );
        void create_periodic_test_set( std::vector<Task_p *> &test_tasks );

        void write_tasks( std::vector<Task *>  &test_tasks );
        void write_tasks_p( std::vector<Task_p *> &test_tasks );
        void load_tasks( std::vector<Task *> &test_tasks );
        void load_tasks_p( std::vector<Task_p *> &test_tasks );

        int task_number;
        double dd_range;
        double dd_tightness;

        bool periodic;
    private:
        std::vector<double> UUnifast_generate_u( int n, double mean_u );
        std::vector<double> generate_log_uniform( int n, double lim_u, double lim_d, int granularity );

};


#endif //GP_SCHEDULING_TASKCREATOR_H
