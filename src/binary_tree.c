#include "../include/binary_tree.h"

void link_right(tree_node_t* parent, tree_node_t* child)
{
    parent->right = child;
    child->parent = parent;
}

void link_left(tree_node_t* parent, tree_node_t* child)
{
    parent->left = child;
    child->parent = parent;
}


tree_node_t* create_node(elem_t data)
{
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    *node = {.data = data, .left = NULL, .right = NULL, .parent = NULL};
    return node;
}

void convert_into_text(tree_node_t* node, FILE* file)
{
    fprintf(file, "(");

    fprintf(file, "<%s> ", node->data);
    if (node->left != NULL) {
        convert_into_text(node->left, file);
    }
    if (node->right != NULL) {
        convert_into_text(node->right, file);
    }
    fprintf(file, ")");
    return;
}

tree_node_t* read_tree(FILE* file)
{
    tree_node_t* parent = create_node((char*) "nill");
    int ch = fgetc(file);

    if (ch == '(') {
        char* string = (char*) calloc(MAX_STRLEN, sizeof(char));
        read_phrase(string, file);

        parent = create_node(string);

        ch = fgetc(file); //read space
        ch = fgetc(file); //read brace

        if (ch == ')') {
            return parent;
        }
        ungetc(ch, file);

        tree_node_t* child = read_tree(file);
        link_left(parent, child);

        child = read_tree(file);
        link_right(parent, child);

        ch = fgetc(file);

        if (ch == ')') {
            return parent;
        }
        ungetc(ch, file);
    }

    assert(parent);

    return parent;
}

void tree_dump(tree_node_t* node, FILE* graph)
{
    node_dump(node, graph);

    if (node->left != NULL)
    {
        fprintf(graph, "    node%p->node%p\n", node, node->left);
        tree_dump(node->left, graph);
    }

    if (node->right != NULL)
    {
        fprintf(graph, "    node%p->node%p\n", node, node->right);
        tree_dump(node->right, graph);
    }

    return;
}

void node_dump(tree_node_t* node, FILE* graph)
{
    assert(node);

    fprintf(graph, "    node%p [shape=Mrecord, style=filled, fillcolor=\"#ba0aae\", color=\"#250228\", label=\"{{ptr = %p | parent = %p} | data = %s | {left = %p | right = %p}}\"];\n", node, node, node->parent, node->data, node->left, node->right);
}

void dump(tree_node_t* node)
{
    assert(node);

    static int counter = 0;
    counter++;

    char file_name[100] = {};
    snprintf(file_name, 100, "dump/graph%d.dot", counter);

    FILE* graph = fopen(file_name, "w");
    assert(graph);

    fprintf(graph, "digraph {\n");
    tree_dump(node, graph);

    fprintf(graph, "}\n");
    char temp[100] = {};
    snprintf(temp, 100, "dot -Tsvg dump/graph%d.dot -o dump/graph%d.svg", counter, counter);

    fclose(graph);
    int err = system(temp);
    if (err != 0) {
        fprintf(stderr, "err = %d\n", err);
    }
}

bool is_leave(tree_node_t* node)
{
    if (node->left == NULL && node->right == NULL) {
        return true;
    }

    return false;
}

void destroy_node(tree_node_t* node)
{
    free(node);
}

void destroy_tree(tree_node_t* root)
{
    if (root->left == NULL && root->right == NULL)
    {
        destroy_node(root);
        return;
    }

    if (root->left != NULL) {
        destroy_tree(root->left);
    }

    if (root->right != NULL) {
        destroy_tree(root->right);
    }
}
