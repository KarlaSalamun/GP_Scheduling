//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_MULNODE_H
#define GP_SCHEDULING_MULNODE_H

#include "AbstractNode.h"

class MulNode : public AbstractNode {
    public:
        MulNode() : AbstractNode() {
            is_terminal = false;
            children_number = 2;
            children.assign( children_number, nullptr );
            name = "Mul";
            depth = 0;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new MulNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> pending_tasks, std::vector<Task *> processed_tasks ) {
            return children[0]->calculate_priority( task, pending_tasks, processed_tasks ) *
                children[1]->calculate_priority( task, pending_tasks, processed_tasks );
        }

        void execute( void *ctx ) {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);
            ctx_->task->set_priority( children[0]->calculate_priority( ctx_->task, ctx_->pending, ctx_->processed )
                                      * children[1]->calculate_priority( ctx_->task, ctx_->pending, ctx_->processed ) );
        }
};


#endif //GP_SCHEDULING_MULNODE_H
