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
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new WNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> pending_tasks, std::vector<Task *> processed_tasks ) {
            return task->weight;
        }
};


#endif //GP_SCHEDULING_WNODE_H
