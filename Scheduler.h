//
// Created by karla on 01. 04. 2020..
//

#ifndef GP_SCHEDULING_SCHEDULER_H
#define GP_SCHEDULING_SCHEDULER_H

#include <vector>
#include "Task_p.h"
#include "Nodes/AbstractNode.h"

class Scheduler {
public:
    Scheduler() {}
    virtual void schedule_next( std::vector<Task_p *> &pending, std::vector<Task_p *> &ready, Task_p *&running, double time );
private:
    virtual void set_start( Task_p *&task, double time );
    virtual void set_end( Task_p *&task, double time );
    virtual bool preempt( const Task_p *t1, const Task_p *t2 );
};


#endif //GP_SCHEDULING_SCHEDULER_H
