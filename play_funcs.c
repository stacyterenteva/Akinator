#include "play_funcs.h"
#include "binary_tree.h"

void talk_with_user(tree_node_t* answer)
{
    printf("Did you pick the %s? (y/n)\n", answer->data);

    char is_answer_correct = 0;
    scanf("%c", &is_answer_correct);

    if (is_answer_correct == 'y') {
        printf("Good attemp, but i win... again\n");
    }

    else if (is_answer_correct == 'n') {
        printf("I don't know this word\n");
        printf("Please, answer the questions, so i can add it in my database\n");
        printf("Input the word you've pickd\n");

        char* correct_answer = (char*) calloc(MAX_STRLEN, sizeof(char));
        scanf("%s", correct_answer);

        printf("What is the difference between %s ans %s, give one word\n", correct_answer, answer->data);

        char* difference = (char*) calloc(MAX_STRLEN, sizeof(char));

        scanf("%s", difference);

        printf("Thank you\n");

        add_new_answer_to_base(answer, difference, correct_answer);
    }

    else {
        printf("Wrong input, you should input y(yes), or n(no), please, try again");
    }
}

tree_node_t* find_user_answer(tree_node_t* node)
{

    assert(node);

    if (node->left == NULL && node->right == NULL) {
        return node;
    }

    printf("Is it %s?(y/n)\n", node->data);

    char answer = 0;
    scanf("%c", &answer);
    getchar();

    while (answer != 'y' && answer != 'n') {
        printf("Wrong input, you should input y(yes), or n(no), please, try again\n");
        scanf("%c", &answer);
        getchar();
    }
    if (answer == 'y') {
        return find_user_answer(node->left);
    }

    else if (answer == 'n') {
        return find_user_answer(node->right);
    }
}

void add_new_answer_to_base(tree_node_t* answer, char* difference, char* correct_answer)
{

    tree_node_t* old_answer = create_node(answer->data);
    tree_node_t* new_answer = create_node(correct_answer);

    answer->data = difference;

    linked_right(answer, old_answer);
    linked_left(answer, new_answer);

}
