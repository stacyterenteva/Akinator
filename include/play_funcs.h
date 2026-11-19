#ifndef PLAY_FUNCS_H
#define PLAY_FUNCS_H

const int MAX_NUM_OF_PROPS = 50;

#define MY_YELLOW "\033[33m"
#define RESET "\033[0m"
#define MY_PURPLE "\033[35m"

#include "binary_tree.h"

enum GAME_STATE {
    GAME_STATE_COUNTINUE,
    GAME_STATE_END
};

enum FRAME {
    FRAME_QUESTION,
    FRAME_USER_WIN,
    FRAME_AKINATOR_WIN
};

tree_node_t* find_user_answer(tree_node_t* node);
void add_new_answer_to_base(tree_node_t* answer, char* difference, char* correct_answer);
void talk_with_user(tree_node_t* answer);

tree_node_t* find_node(char* user_word, tree_node_t* node);
void create_definition(tree_node_t* node, char** array, int* num_of_prop);
void compare_two_words(char* first_user_word, char* second_user_word, tree_node_t* root);

void end_game(Music song, GAME_STATE* state);
void begin_game(Music song);

tree_node_t* find_user_answer_g(tree_node_t* node, Music song, int width);
void talk_with_user_g(tree_node_t* answer, Music song, int width);

#endif /* PLAY_FUNCS_H */
