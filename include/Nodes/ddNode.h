//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_DDNODE_H
#define GP_SCHEDULING_DDNODE_H

#include "AbstractNode.h"

class ddNode : public AbstractNode {
    public:
        ddNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "dd";
            depth = 0;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new ddNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> , std::vector<Task *>, size_t ) {
            return task->get_abs_due_date();
        }

        void execute( void *ctx )
        {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);
            ctx_->task->set_priority( ctx_->task->get_abs_due_date() );
        }
};

#endif //GP_SCHEDULING_DDNODE_H
