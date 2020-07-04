//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_SDNODE_H
#define GP_SCHEDULING_SDNODE_H

#include "AbstractNode.h"

class SDNode : public AbstractNode {
    public:
        SDNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "SD";
            depth = 1;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new SDNode( *this );
        }

        double calculate_priority( Task *&, std::vector<Task *> pending_tasks, std::vector<Task *> processed_tasks, size_t ) {
            double sum = 0;

            for( auto & element : pending_tasks ) {
                sum+=element->get_abs_due_date();
            }

            for( auto & element : processed_tasks ) {
                sum+=element->get_abs_due_date();
            }

            return sum;
        }

        void execute( void *ctx )
        {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);

            double sum = 0;

            for( auto & element : ctx_->pending ) {
                sum+=element->get_abs_due_date();
            }

            for( auto & element : ctx_->processed ) {
                sum+=element->get_abs_due_date();
            }
            ctx_->task->set_priority( sum );
        }
};

#endif //GP_SCHEDULING_SDNODE_H
