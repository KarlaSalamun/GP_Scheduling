//
// Created by karla on 04. 12. 2019..
//
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <queue>
#include "AbstractNode.h"

AbstractNode::AbstractNode()
{}

//AbstractNode::~AbstractNode()
//{
//    for( size_t i=0; i<children.size(); i++ ) {
//        delete children[i];
//        children[i] = nullptr;
//    }
//}

AbstractNode::~AbstractNode() = default;

AbstractNode *AbstractNode::get_child( unsigned int index )
{
    if( index >= this->children.size() ) {
        return NULL;
    }
     return this->children[index];
}

int AbstractNode::calculate_children()
{
    subtree_num = 0;
    depth = 1;
    for( size_t i=0; i<children.size(); i++ ) {
        subtree_num += children[i]->calculate_children() + 1;
        depth = std::max( depth, children[i]->depth + 1 );
    }
    return subtree_num;
}

AbstractNode *AbstractNode::pick_random( AbstractNode *&node, int rand_depth )
{
    if( rand_depth == 0 ) {
        return node;
    }
    if ( rand_depth > depth ) {
        rand_depth = depth;             // kako se ovo hendla, na ovaj nacin preferiram vecu dubinu
    }
    int random_child = rand() % children.size();
    return pick_random( children[random_child], rand_depth-1 );
}

void AbstractNode::replace_random( AbstractNode *&new_node )
{
    int rand_depth;
    int random_node = rand() % children.size();
    if( children[random_node]->depth == 0 ) {
        rand_depth = 0;
    }
    else {
        rand_depth = rand() % children[random_node]->depth;
    }
    AbstractNode *random = pick_random( children[random_node], rand_depth );

    if( random->is_terminal ) {
        return;
    }

    int random_index = rand() % random->children_number;

    std::swap( random->children[random_index], new_node );
    random->depth = new_node->depth;

    this->depth = ( this->depth > new_node->depth + this->depth - random->depth ) ?
                  this->depth : ( new_node->depth + this->depth - random->depth );

}

