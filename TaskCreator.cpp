//
// Created by karla on 09. 03. 2020..
//

#include <random>
#include "TaskCreator.h"

void TaskCreator::create_test_set( std::vector<Task *> &test_tasks )
{
    double sum_1 = 0;
    double sum_2 = 0;

    test_tasks.resize( task_number );
    for( int i=0; i<test_tasks.size(); i++ ) {
        test_tasks[i] = std::move( new Task() );
        test_tasks[i]->time_started = 0;
        test_tasks[i]->duration = 1 + rand() % 100; // integer value from 1 to 100
        test_tasks[i]->weight = static_cast<double>( 1 + rand() % 100 ) / 100.; // 0.01 to 1 with 0.01 increment
        sum_1 += test_tasks[i]->duration * ( 1 - dd_tightness - dd_range/2. );
        sum_2 += test_tasks[i]->duration * ( 1 - dd_tightness + dd_range/2. );
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis( sum_1, sum_2 );

    for( int i=0; i<test_tasks.size(); i++ ) {
//        test_tasks[i]->due_date = sum_1 + static_cast<double>( rand() / static_cast<double>(RAND_MAX) ) * ( sum_2 - sum_1 );
        test_tasks[i]->due_date = dis(gen);
    }
}