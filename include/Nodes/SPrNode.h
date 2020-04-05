//
// Created by karla on 06. 03. 2020..
//

#ifndef GP_SCHEDULING_SPRNODE_H
#define GP_SCHEDULING_SPRNODE_H

#include "AbstractNode.h"

class SPrNode : public AbstractNode {
    public:
        SPrNode() : AbstractNode() {
            is_terminal = true;
            children_number = 0;
            children.assign( children_number, nullptr );
            name = "SPr";
            depth = 1;
        }

        void copy_node( AbstractNode *&copy ) override {
            copy = new SPrNode( *this );
        }

        double calculate_priority( Task *&, std::vector<Task *> pending_tasks, std::vector<Task *> ) {

            double sum = 0;
            for( auto & element : pending_tasks ) {
                sum += element->get_duration();
            }
            return sum;
        }
};


#endif //GP_SCHEDULING_SPRNODE_H
