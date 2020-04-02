//
// Created by karla on 09. 03. 2020..
//
#include <cassert>
#include <random>
#include <cstdio>
#include "TaskCreator.h"
#include "Task_p.h"

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
        test_tasks[i]->due_date = sum_1 + static_cast<double>( rand() / static_cast<double>(RAND_MAX) ) * ( sum_2 - sum_1 );
        test_tasks[i]->due_date = dis(gen);
    }
}

void TaskCreator::create_periodic_test_set( std::vector<Task_p *> &test_tasks )
{
    test_tasks.resize( task_number );

    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist_dd(0.5, 1);

    std::vector<double> u_values = UUnifast_generate_u( test_tasks.size(), 1 );
    std::vector<double> T_values = generate_log_uniform( test_tasks.size(), 100, 10, 10 );

    for( int i=0; i<test_tasks.size(); i++ ) {
        test_tasks[i] = std::move( new Task_p );
        test_tasks[i]->period = T_values[i];
        // test_tasks[i]->phase = static_cast<double>( 0.5 * (rand() % 2) + ( rand() % 3 ) ); // 1 to 10
        test_tasks[i]->phase = 0;
        test_tasks[i]->instance = 1;
        assert( u_values[i]!=0 );
        test_tasks[i]->duration = u_values[i] * test_tasks[i]->period;
        // test_tasks[i]->rel_due_date = test_tasks[i]->period * dist_dd(e2);
        test_tasks[i]->due_date = test_tasks[i]->period;
        test_tasks[i]->id = i;

    }
}

void TaskCreator::write_tasks( std::vector<Task *>  &test_tasks )
{
    FILE *fd = fopen( "../task_set.txt", "w+" );
    for( auto & element: test_tasks ) {
        fprintf( fd, "%f %f %f\n", element->due_date, element->weight, element->duration );
    }
    fclose(fd);
}

void TaskCreator::write_tasks_p( std::vector<Task_p *> &test_tasks )
{
    FILE *fd = fopen( "../task_set.txt", "w+" );
    for( int i=0; i<test_tasks.size(); i++ ) {
        fprintf(fd, "%d %.2f %.2f %.2f %.2f\n",
                test_tasks[i]->id, test_tasks[i]->phase, test_tasks[i]->period, test_tasks[i]->duration,
                test_tasks[i]->due_date);
    }
    fclose(fd);
}

void TaskCreator::load_tasks_p( std::vector<Task_p *> &test_tasks )
{
    test_tasks.assign( task_number, 0 );
    FILE *fd = fopen( "../task_set.txt", "r" );
    fseek(fd, 0L, SEEK_SET);

    for( int i=0; i<test_tasks.size(); i++ ) {
        test_tasks[i] = std::move( new Task_p() );
        int retval = fscanf( fd, "%d %lf %lf %lf %lf",
                &test_tasks[i]->id, &test_tasks[i]->phase, &test_tasks[i]->period, &test_tasks[i]->duration, &test_tasks[i]->due_date );
    }
    fclose(fd);
}

void TaskCreator::load_tasks( std::vector<Task *> &test_tasks )
{
    test_tasks.assign( task_number, 0 );
    FILE *fd = fopen( "../task_set.txt", "r" );
    fseek(fd, 0L, SEEK_SET);

    for( int i=0; i<test_tasks.size(); i++ ) {
        test_tasks[i] = std::move( new Task() );
        test_tasks[i]->time_started = 0;
        int retval = fscanf( fd, "%lf %lf %lf", &test_tasks[i]->due_date, &test_tasks[i]->weight, &test_tasks[i]->duration );
    }

    fclose(fd);
}

std::vector<double> TaskCreator::UUnifast_generate_u( int n, double mean_u )
{
    std::vector<double> result;
    result.assign( n, 0 );
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 1);
    double sum_u = mean_u;

    for( int i=0; i<n-1; i++ ) {
        double coeff = (1 + rand() % 100) / 100.;
        double next_sum_u = sum_u * pow( coeff, static_cast<double>( 1. / ( n-i ) ) );
        result[i] = sum_u - next_sum_u;
        assert( result[i]!=0 );
        sum_u = next_sum_u;
    }

    result[n-1] = sum_u;
    return result;
}

std::vector<double> TaskCreator::generate_log_uniform( int n, double lim_u, double lim_d, int granularity )
{
    std::vector<double> result(n);
    std::vector<double> r_factor(n);
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist( log( lim_d ), log( lim_u + granularity ) );

    for( int i=0; i<n; i++ ) {
        r_factor[i] = dist(e2);
        result[i] = floor( exp( r_factor[i] ) / granularity ) * granularity;
    }
    return result;
}