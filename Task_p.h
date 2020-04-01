//
// Created by karla on 01. 04. 2020..
//

#ifndef GP_SCHEDULING_TASK_P_H
#define GP_SCHEDULING_TASK_P_H

#include "Task.h"

class Task_p : public Task  {
    public:
        double phase;
        int instance;
        int id;
        double period;
        double arrival_time;
        double abs_due_date;
        double rel_due_date;
        double time_ended;
        double tardiness;
        double remaining;
        bool isPreempted;

        double compute_tardiness();
        void update_tardiness( double time );
        void set_arrival_time();
        void set_abs_dd();
        void update_params();
        bool isReady( double time );
        bool isFinished( double time );
        void inc_instance();
        void set_remaining( double time );

        Task_p( double phase, int instance, double period, double rel_due_date ) :
                phase( phase ), instance( instance ), period( period ), rel_due_date( rel_due_date )
        {
            tardiness = 0;
            isPreempted = false;
        }
        Task_p() {}
        ~Task_p() {}
};


#endif //GP_SCHEDULING_TASK_P_H
