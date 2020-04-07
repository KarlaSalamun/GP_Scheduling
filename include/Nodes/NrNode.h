//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_NRNODE_H
#define GP_SCHEDULING_NRNODE_H


#include "AbstractNode.h"

class NrNode : public AbstractNode {
    public:
        NrNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "Nr";
            depth = 1;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new NrNode( *this );
        }

        double calculate_priority( Task *&, std::vector<Task *> pending_tasks, std::vector<Task *> ) {
            return pending_tasks.size();
        }

        void execute( void *ctx )
        {
            struct task_ctx *ctx_ = reinterpret_cast<struct task_ctx *>(ctx);
            ctx_->task->set_priority( ctx_->pending.size() );
        }
};


#endif //GP_SCHEDULING_NRNODE_H
