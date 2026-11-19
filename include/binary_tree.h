#ifndef BINARY_TREE_H

#define BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "raylib.h"

#include "common_funcs.h"

typedef char* elem_t;

struct tree_node_t
{
    elem_t data;
    tree_node_t* left;
    tree_node_t* right;
    tree_node_t* parent;
};

struct tree_t
{
    tree_node_t root;
};

tree_node_t* create_node(elem_t data);
void destroy_node(tree_node_t* node);
void destroy_tree(tree_node_t* root);

void link_right(tree_node_t* parent, tree_node_t* child);
void link_left(tree_node_t* parent, tree_node_t* child);

void node_dump(tree_node_t* node, FILE* graph);
void tree_dump(tree_node_t* node, FILE*  graph);
void dump(tree_node_t* node);

void convert_into_text(tree_node_t* node, FILE* file);
tree_node_t* read_tree(FILE* file);
bool is_leave(tree_node_t* node);

#endif /* BINARY_TREE_H */
