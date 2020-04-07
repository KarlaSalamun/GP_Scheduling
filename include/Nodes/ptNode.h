//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_PTNODE_H
#define GP_SCHEDULING_PTNODE_H

#include "AbstractNode.h"

class ptNode : public AbstractNode {
    public:
        ptNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "pt";
            depth = 1;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new ptNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> , std::vector<Task *> ) {
            return task->get_duration();
        }

        void execute( void *ctx )
        {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);
            ctx_->task->set_priority( ctx_->task->get_duration() );
        }
};


#endif //GP_SCHEDULING_PTNODE_H
