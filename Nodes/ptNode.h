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
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new ptNode( *this );
        }

        double calculate_priority( Task &task, std::vector<Task> pending_tasks, std::vector<Task> processed_tasks ) {
            return task.duration;
        }
};


#endif //GP_SCHEDULING_PTNODE_H
