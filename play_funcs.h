#ifndef PLAY_FUNCS_H
#define PLAY_FUNCS_H

#include "binary_tree.h"

tree_node_t* find_user_answer(tree_node_t* node);
void add_new_answer_to_base(tree_node_t* answer, char* difference, char* correct_answer);
void talk_with_user(tree_node_t* answer);

#endif /* PLAY_FUNCS_H */
