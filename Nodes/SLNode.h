//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_SLNODE_H
#define GP_SCHEDULING_SLNODE_H

#include <cstdio>

class SLNode : public AbstractNode {
    public:
        SLNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "SL";
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new SLNode( *this );
        }

        double calculate_priority( Task &task, std::vector<Task> pending_tasks, std::vector<Task> processed_tasks ) {
            return std::max( task.due_date - task.duration - task.time_started, 0. );
        }
};

#endif //GP_SCHEDULING_SLNODE_H
