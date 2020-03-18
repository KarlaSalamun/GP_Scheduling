//
// Created by karla on 10. 12. 2019..
//

#ifndef SANTAFE_TREECONSTRUCTOR_H
#define SANTAFE_TREECONSTRUCTOR_H

#include <string>
#include "Nodes/AbstractNode.h"
#include "Nodes/ddNode.h"
#include "Nodes/AddNode.h"
#include "Nodes/DivNode.h"
#include "Nodes/MulNode.h"
#include "Nodes/NrNode.h"
#include "Nodes/PosNode.h"
#include "Nodes/ptNode.h"
#include "Nodes/SDNode.h"
#include "Nodes/SLNode.h"
#include "Nodes/SPrNode.h"
#include "Nodes/SubNode.h"
#include "Nodes/WNode.h"

class TreeConstructor {
    public:
        void get_random_terminal_node( AbstractNode *&new_node );
        void get_random_function_node( AbstractNode *&new_node );
        void get_random_any( AbstractNode *&new_node );
        void construct_tree_full( int max_depth, AbstractNode *&root );
        void construct_tree_grow( int max_depth, AbstractNode *&root );
        void destroy_tree( AbstractNode *&root );
        void rehash_tree( AbstractNode *&root );
        void draw_tree( AbstractNode *&root, std::string filename );
        void check_tree(AbstractNode *&root, int depth);
        void get_depth( AbstractNode *&root );
};


#endif //SANTAFE_TREECONSTRUCTOR_H
