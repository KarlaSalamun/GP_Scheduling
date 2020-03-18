//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_POSNODE_H
#define GP_SCHEDULING_POSNODE_H

#include "AbstractNode.h"

class PosNode : public AbstractNode {
    public:
        PosNode() : AbstractNode() {
            is_terminal = false;
            children_number = 1;
            children.assign( children_number, nullptr );
            name = "Pos";
            depth = 0;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new PosNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> pending_tasks, std::vector<Task *> processed_tasks ) {
            return std::max( children[0]->calculate_priority( task, pending_tasks, processed_tasks ), 0. );
        }
};


#endif //GP_SCHEDULING_POSNODE_H
