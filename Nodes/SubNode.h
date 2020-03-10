//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_SUBNODE_H
#define GP_SCHEDULING_SUBNODE_H

#include "AbstractNode.h"

class SubNode : public AbstractNode {
    public:
        SubNode() : AbstractNode() {
            is_terminal = false;
            children_number = 2;
            children.assign( children_number, nullptr );
            name = "Sub";
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new SubNode( *this );
        }

        double calculate_priority( Task *&task, std::vector<Task *> pending_tasks, std::vector<Task *> processed_tasks ) {
            return children[0]->calculate_priority( task, pending_tasks, processed_tasks ) -
                children[1]->calculate_priority( task, pending_tasks, processed_tasks );
        }
};


#endif //GP_SCHEDULING_SUBNODE_H
