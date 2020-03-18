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

        double calculate_priority( Task *&task, std::vector<Task *> pending_tasks, std::vector<Task *> processed_tasks ) {
            return task->due_date;
        }
};

#endif //GP_SCHEDULING_DDNODE_H
