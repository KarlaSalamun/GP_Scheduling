//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_TASK_H
#define GP_SCHEDULING_TASK_H


class Task {
    public:
        double priority;
        double due_date;
        double weight;
        double duration;
        double time_started;
        double compute_tardiness();
        Task( double duration, double weight, double due_date ) :
            duration( duration ), due_date( due_date ), weight( weight ) {}
        ~Task() {}
};


#endif //GP_SCHEDULING_TASK_H
