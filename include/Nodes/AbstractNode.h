//
// Created by karla on 04. 12. 2019..
//

#ifndef SANTAFE_ABSTRACTNODE_H
#define SANTAFE_ABSTRACTNODE_H

#include <vector>
#include <array>
#include <queue>
#include "Task.h"
#include "Simulator.h"

class AbstractNode {
    public:
        std::vector<AbstractNode *> children;
        int depth;
        int subtree_num;
        int children_number;
        int id;
        bool is_terminal;
        const char *name;

        AbstractNode();
        virtual ~AbstractNode();

        virtual double calculate_priority ( Task *&task, std::vector<Task *> pending_tasks,
                std::vector<Task *> processed_tasks, size_t time ) = 0;

        virtual void execute( void* ) = 0;

        AbstractNode *get_child( unsigned int index );
        virtual void copy_node( AbstractNode *&original ) = 0;

        int calculate_children();

        AbstractNode *pick_random( AbstractNode *&node, int rand_depth );
        void replace_random(AbstractNode *&new_node );
};

#endif //SANTAFE_ABSTRACTNODE_H
