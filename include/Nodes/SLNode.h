//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_SLNODE_H
#define GP_SCHEDULING_SLNODE_H

#include <cstdio>
#include "AbstractNode.h"

class SLNode : public AbstractNode {
    public:
        SLNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "SL";
            depth = 1;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new SLNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> , std::vector<Task *> ) {
            return std::max( task->get_abs_due_date() - task->get_duration() - task->get_time_started(), 0. );
        }

        void execute( void *ctx )
        {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);
            ctx_->task->set_priority( std::max( ctx_->task->get_abs_due_date() - ctx_->task->get_duration() - ctx_->task->get_time_started(), 0. ) );
        }
};

#endif //GP_SCHEDULING_SLNODE_H
