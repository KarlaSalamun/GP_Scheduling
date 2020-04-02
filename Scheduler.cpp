//
// Created by karla on 01. 04. 2020..
//

#include "Scheduler.h"
#include <algorithm>
#include <cstdio>
#include "Scheduler.h"

struct {
    bool operator()(Task_p *a, Task_p *b) const
    {
        return a->priority < b->priority;
    }
} customLess;

void Scheduler::schedule_next( std::vector<Task_p *> &pending, std::vector<Task_p *> &ready, Task_p *&running, double time )
{

    for( auto & element : ready ) {
        element->priority = heuristic->calculate_priority( reinterpret_cast<Task *&>(element),
                                                           reinterpret_cast<const std::vector<Task *> &>(ready),
                                                           reinterpret_cast<const std::vector<Task *> &>(pending) );
    }
    std::sort( ready.begin(), ready.end(), customLess );

    if( running ) {
        if ( preempt( ready[0], running ) ) {
//            printf( "task %d is preempted, ", running->id );
            running->isPreempted = true;
            running->set_remaining( time );
//            printf( "remaining time %f\n", running->remaining );
            std::swap( ready[0], running );
            set_start( running, time );
        }
    }
    else {
        running = std::move( ready[0] );
        set_start( running, time );
        // running->set_remaining( time );
        ready.erase( ready.begin() );
    }

//    printf( "task %d is running!\n", running->id );
}

void Scheduler::set_start( Task_p *&task, double time )
{
    task->time_started = time;
}

void Scheduler::set_end( Task_p *&task, double time )
{
    task->time_ended = time;
}

bool Scheduler::preempt( const Task_p *t1, const Task_p *t2 )
{
    return t1->priority < t2->priority;
}
