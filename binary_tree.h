#ifndef BINARY_TREE_H

#define BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef char* elem_t;

const int MAX_STRLEN = 100;

struct tree_node_t
{
    elem_t data;
    tree_node_t* left;
    tree_node_t* right;
};

struct tree_t
{
    tree_node_t root;
};

tree_node_t* create_node(elem_t data);
void destroy_node();
void linked_right(tree_node_t* parent, tree_node_t* child);
void linked_left(tree_node_t* parent, tree_node_t* child);
void convert_into_text(tree_node_t* node, FILE* file);
void node_dump(tree_node_t* node, FILE* graph);
void tree_dump(tree_node_t* node, FILE*  graph);
void dump(tree_node_t* node);
tree_node_t* read_tree(FILE* file);

#endif /* BINARY_TREE_H */
