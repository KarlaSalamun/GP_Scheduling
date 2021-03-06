//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_DIVNODE_H
#define GP_SCHEDULING_DIVNODE_H

#include <cmath>
#include "AbstractNode.h"

class DivNode : public AbstractNode {
    public:
        DivNode() : AbstractNode() {
            is_terminal = false;
            children_number = 2;
            children.assign( children_number, nullptr );
            name = "Div";
            depth = 0;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new DivNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> pending_tasks, std::vector<Task *>processed_tasks ) override
        {
            return children[0]->calculate_priority( task, pending_tasks, processed_tasks ) /
                children[1]->calculate_priority( task, pending_tasks, processed_tasks );
        }

        void execute( void *ctx ) override
        {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);
            double tmp_result = children[1]->calculate_priority( ctx_->task, ctx_->pending, ctx_->processed );
            ctx_->task->set_priority( children[0]->calculate_priority( ctx_->task, ctx_->pending, ctx_->processed )
                                      / ( std::isgreater( fabs(tmp_result), 0 ) ? tmp_result : 1 ) );
        }
};


#endif //GP_SCHEDULING_DIVNODE_H
