//
// Created by karla on 10. 12. 2019..
//
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <string>
#include <queue>
#include <cassert>
#include "TreeConstructor.h"

#define TERM_NODES 7
#define FUNC_NODES 5

using std::queue;

// FIXME stavi parametre preko reference svugdje

void TreeConstructor::get_random_terminal_node( AbstractNode *&new_node )
{
    int random = rand() % TERM_NODES;
    switch(random) {
        case 0:
            new_node = new ddNode;
            break;
        case 1:
            new_node = new NrNode;
            break;
        case 2:
            new_node = new ptNode;
            break;
        case 3:
            new_node = new SDNode;
            break;
        case 4:
            new_node = new SLNode;
            break;
        case 5:
            new_node = new SPrNode;
            break;
        case 6:
            new_node = new WNode;
            break;
        default:
            new_node = new ddNode;
            break;
    }
}

void TreeConstructor::get_random_function_node( AbstractNode *&new_node )
{
    int random = rand() % FUNC_NODES;
    switch(random) {
        case 0:
            new_node =  new AddNode;
            break;
        case 1:
            new_node = new DivNode;
            break;
        case 2:
            new_node = new MulNode;
            break;
        case 3:
            new_node = new SubNode;
            break;
        case 4:
            new_node = new PosNode;
            break;
        default:
            new_node = new PosNode;
            break;
    }
}

void TreeConstructor::get_random_any( AbstractNode *&new_node )
{
    int random = rand() % ( TERM_NODES + FUNC_NODES );
    switch(random) {
        case 0:
            new_node = new AddNode;
            break;
        case 1:
            new_node = new MulNode;
            break;
        case 2:
            new_node = new SubNode;
            break;
        case 3:
            new_node = new DivNode;
            break;
        case 4:
            new_node = new PosNode;
            break;
        case 5:
            new_node = new ddNode;
            break;
        case 6:
            new_node = new NrNode;
            break;
        case 7:
            new_node = new ptNode;
            break;
        case 8:
            new_node = new SDNode;
            break;
        case 9:
            new_node = new SLNode;
            break;
        case 10:
            new_node = new SPrNode;
            break;
        case 11:
            new_node = new WNode;
            break;
        default:
            new_node = new NrNode;
            break;
    }
}

void TreeConstructor::construct_tree_full( int max_depth, AbstractNode *&root )
{
    get_random_function_node( root );
    int depth = rand() % max_depth + 1;
    int identifier = 0;
    root->id = identifier;
    identifier++;
    std::queue<AbstractNode *> queue;
    queue.push( root );

    int ref_depth = 1;
    while( ref_depth < depth - 1 ) {
        int size = queue.size();
        for( int i=0; i<size; i++ ) {
            AbstractNode *current = queue.front();
            queue.pop();
            current->depth = ref_depth;
            for( int j=0; j<current->children_number; j++ ) {
                get_random_function_node( current->children[j] );
                current->children[j]->id = identifier;
                identifier++;
                queue.push( current->children[j] );
            }
        }
        ref_depth++;
    }

    int size = queue.size();
    for( int i=0; i<size; i++ ) {
        AbstractNode *current = queue.front();
        queue.pop();
        current->depth = ref_depth;
        for( int j=0; j<current->children_number; j++ ) {
            get_random_terminal_node( current->children[j] );
            current->children[j]->id = identifier;
            identifier++;
            current->children[j]->depth = depth;
        }
    }
    root->depth = depth;
}

void TreeConstructor::construct_tree_grow( int, AbstractNode *&root )
{
//    int depth = rand() % max_depth + 1;
    int depth = 5;
    int identifier = 0;
    get_random_function_node( root );
    root->id = identifier;
    identifier++;

    std::queue<AbstractNode *> queue;
    queue.push( root );

    int ref_depth = 1;
    while( ref_depth < depth-1 ) {
        int size = queue.size();
        for( int i=0; i<size; i++ ) {
            AbstractNode *current = queue.front();
            queue.pop();
            current->depth = ref_depth;
            if( current->is_terminal ) {
                continue;
            }
            for( int j=0; j<current->children_number; j++ ) {
                get_random_any( current->children[j] );
                current->children[j]->id = identifier;
                identifier++;
                queue.push( current->children[j] );
            }
        }
        ref_depth++;
    }
    int size = queue.size();
    for( int i=0; i<size; i++ ) {
        AbstractNode *current = queue.front();
        queue.pop();
        if( current->is_terminal ) {
            continue;
        }
        for( int j=0; j<current->children_number; j++ ) {
            get_random_terminal_node( current->children[j] );
            current->children[j]->id = identifier;
            identifier++;
            current->children[j]->depth = depth;
        }
    }
    root->depth = depth;
}

void TreeConstructor::rehash_tree( AbstractNode *&root )
{
    std::queue<AbstractNode *> queue;
    queue.push( root );

    int identifier = 0;

    while( !queue.empty() ) {
        AbstractNode *current = queue.front();
        queue.pop();
        current->id = identifier++;

        for( int i=0; i<current->children_number; i++ ) {
            queue.push( current->children[i] );
        }
    }
}

void TreeConstructor::get_depth( AbstractNode *&root )
{
    if( root == nullptr ) {
        return;
    }

    if( root->is_terminal ) {
        root->depth = 1;
    }

    else {
        root->depth += 1;
        for( size_t i=0; i<root->children.size(); i++ ) {
            get_depth( root->children[i] );
        }
    }
}

// TODO napravi BFS pomocnu funkciju koja radi obilazak stabla
void TreeConstructor::draw_tree( AbstractNode *&root, std::string filename )
{
    std::queue<AbstractNode *> queue;
    std::string tmp = "../graphs/";

    //strcat( tmp, filename );
    FILE *fp = fopen( (tmp+filename).c_str(), "w+");
    fprintf( fp, "digraph D {\n\n" );


    fprintf( fp, "\t%d [label=\"%s\"]\n", root->id, root->name );

    queue.push( root );
    while( !queue.empty() ) {
        AbstractNode *current = queue.front();
        queue.pop();

        for (int i = 0; i < current->children_number; i++) {
            fprintf(fp, "\t%d [label=\"%s\"]\n", current->children[i]->id, current->children[i]->name);
            fprintf(fp, "\t%d -> %d;\n", current->id, current->children[i]->id);
            queue.push(current->children[i]);
        }
    }

    fprintf( fp, "}\n" );
    fclose( fp );
}

void TreeConstructor::check_tree(AbstractNode *&root, int depth)
{
    AbstractNode *current;

//    assert( depth == root->depth );
    depth = root->depth;

    current = root;
    if( current != nullptr ) {
        for (size_t i = 0; i < current->children.size(); i++) {
            if (current->children[i] != nullptr) {
                check_tree(current->children[i], depth - 1);
            }
        }
    }
}

void TreeConstructor::custom_tree( AbstractNode *&root )
{
    root = new MulNode;
    root->children[0] = new ptNode;
    root->children[1] = new DivNode;
    root->children[1]->children[0] = new SDNode;
    root->children[1]->children[1] = new DivNode;
    root->children[1]->children[1]->children[0] = new SDNode;
    root->children[1]->children[1]->children[1] = new ptNode;
}

