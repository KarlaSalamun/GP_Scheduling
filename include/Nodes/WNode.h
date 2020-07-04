//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_WNODE_H
#define GP_SCHEDULING_WNODE_H


#include "AbstractNode.h"

class WNode : public AbstractNode {
    public:
        WNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "W";
            depth = 1;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new WNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *>, std::vector<Task *>, size_t ) {
            return task->get_weight();
        }

        void execute( void *ctx ) {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);
            ctx_->task->set_priority( ctx_->task->get_weight() );
        }
};


#endif //GP_SCHEDULING_WNODE_H
