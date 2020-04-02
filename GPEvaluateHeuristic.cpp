//
// Created by karla on 06. 03. 2020..
//
#include <queue>
#include <chrono>
#include <cstdio>
#include <algorithm>
#include "GPEvaluateHeuristic.h"
#include "PeriodicSimulator.h"

struct {
    bool operator()(Task *a, Task *b) const
    {
        return a->priority < b->priority;
    }
} customLess;

// TODO implementiraj template u headeru da ne includas cpp
template <typename T>
double GPEvaluateHeuristic<T>::get_value( TreeSolution<AbstractNode *> &solution )
{
    //TaskCreator *tc = new TaskCreator( 50, 0.6, 0.6 );
    //TaskCreator( int task_number, double dd_range, double dd_tightness )
    double twt = 0;
    double time = 0;

    pending_tasks = test_tasks;
    processed_tasks.clear();

    if( periodic ) {
        PeriodicSimulator *simulator = new PeriodicSimulator( 0.1, 1000, solution.data );
        simulator->set_test_tasks(reinterpret_cast<const std::vector<Task_p *> &>( pending_tasks ) );

        simulator->reset_params();

        simulator->total_tardiness = 0;
        simulator->missed = 0;
        simulator->run();
        return simulator->total_tardiness;
        for (int i = 0; i < pending_tasks.size(); i++) {
            pending_tasks[i]->priority = solution.data->calculate_priority(reinterpret_cast<Task *&>(pending_tasks[i]),
                                                                           reinterpret_cast<const std::vector<Task *> &>(pending_tasks),
                                                                           reinterpret_cast<const std::vector<Task *> &>(processed_tasks));
        }
    }

    else {
        while( pending_tasks.size() > 0 ) {
            for (int i = 0; i < pending_tasks.size(); i++) {
                pending_tasks[i]->priority = solution.data->calculate_priority(
                        reinterpret_cast<Task *&>(pending_tasks[i]),
                        reinterpret_cast<const std::vector<Task *> &>(pending_tasks),
                        reinterpret_cast<const std::vector<Task *> &>(processed_tasks));
            }

            std::sort(pending_tasks.begin(), pending_tasks.end(), customLess);
            pending_tasks[0]->time_started = time;
            twt += pending_tasks[0]->compute_tardiness() * pending_tasks[0]->weight;
            time += pending_tasks[0]->duration;
            processed_tasks.push_back(pending_tasks[0]);
            pending_tasks.erase(pending_tasks.begin());
        }
        return twt;
    }
}
