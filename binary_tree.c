#include "binary_tree.h"

void linked_right(tree_node_t* parent, tree_node_t* child)
{
    parent->right = child;
}

void linked_left(tree_node_t* parent, tree_node_t* child)
{
    parent->left = child;
}

tree_node_t* create_node(elem_t data)
{
    tree_node_t* node = (tree_node_t*) calloc(3, sizeof(elem_t));
    *node = {.data = data, .left = NULL, .right = NULL};
    return node;
}

void convert_into_text(tree_node_t* node, FILE* file)
{
    fprintf(file, "(");

    fprintf(file, "%s ", node->data);
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
    tree_node_t* parent = create_node("nill");
    int ch = fgetc(file);

    if (ch == '(') {
        char* a = (char*) calloc(100, sizeof(char));
        fscanf(file, "%s", a);

        parent = create_node(a);

        ch = fgetc(file); //read space
        ch = fgetc(file); //read brace

        if (ch == ')') {
            return parent;
        }
        ungetc(ch, file);

        tree_node_t* child = read_tree(file);
        linked_left(parent, child);

        child = read_tree(file);
        linked_right(parent, child);

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

    static int tree_dump_counter = 0;
    tree_dump_counter++;

    node_dump(node, graph);

    if (node->left != NULL)
    {
        fprintf(graph, "    node%x->node%x\n", node, node->left);
        tree_dump(node->left, graph);
    }

    if (node->right != NULL)
    {
        fprintf(graph, "    node%x->node%x\n", node, node->right);
        tree_dump(node->right, graph);
    }

    return;
}

void node_dump(tree_node_t* node, FILE* graph)
{
    assert(node);

    fprintf(graph, "    node%x [shape=Mrecord, style=filled, fillcolor=\"#ba0aae\", color=\"#250228\", label=\"{ptr = %x | data = %s | {left = %x | right = %x}}\"];\n", node, node, node->data, node->left, node->right);
}

void dump(tree_node_t* node)
{
    static int counter = 0;
    counter++;

    char file_name[100] = {};
    snprintf(file_name, 100, "graph%d.dot", counter);

    FILE* graph = fopen(file_name, "w");
    assert(graph);

    fprintf(graph, "digraph {\n");
    tree_dump(node, graph);
    fprintf(graph, "}\n");
    char temp[100] = {};
    snprintf(temp, 100, "dot -Tsvg graph%d.dot -o graph%d.svg", counter, counter);
    fclose(graph);
    system(temp);
}
