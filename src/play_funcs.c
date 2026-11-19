#include "../include/play_funcs.h"
#include "../include/binary_tree.h"
#include <string.h>

void talk_with_user(tree_node_t* answer)
{
    assert(answer);

    printf("Did you pick the %s? (y/n)\n", answer->data);

    char is_answer_correct = 0;
    scanf("%c", &is_answer_correct);
    getchar();

    if (is_answer_correct == 'y') {
        printf("Good attemp, but i win... again\n");
    }

    else if (is_answer_correct == 'n') {
        printf("I don't know this word\n");
        printf("Please, answer the questions, so i can add it in my database\n");
        printf("Input the word you've picked\n");

        char* correct_answer = (char*) calloc(MAX_STRLEN, sizeof(char));
        get_string(correct_answer, MAX_STRLEN);

        printf("What is the difference between %s and %s, give one word\n", correct_answer, answer->data);

        char* difference = (char*) calloc(MAX_STRLEN, sizeof(char));

        get_string(difference, MAX_STRLEN);

        printf("Thank you\n");

        add_new_answer_to_base(answer, difference, correct_answer);
        free(difference);
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

    return node;
}

void add_new_answer_to_base(tree_node_t* answer, char* difference, char* correct_answer)
{

    assert(answer);
    assert(difference);
    assert(correct_answer);

    tree_node_t* old_answer = create_node(answer->data);
    tree_node_t* new_answer = create_node(correct_answer);

    answer->data = difference;

    link_right(answer, old_answer);
    link_left(answer, new_answer);
}

tree_node_t* find_node(char* user_word, tree_node_t* node)
{

    if (strcmp(node->data, user_word) == 0) {
        if (is_leave(node)) {
            return node;
        }

        return NULL;
    }

    if (node->left != NULL) {
        tree_node_t* new_node = find_node(user_word, node->left);
        if (new_node != NULL) {
            return new_node;
        }
    }

    if (node->right != NULL) {
        tree_node_t* new_node = find_node(user_word, node->right);
        if (new_node != NULL) {
            return new_node;
        }
    }

    return NULL;
}

void create_definition(tree_node_t* node, char** array, int* num_of_prop)
{
    if (node->parent == NULL) {
        return;
    }
    tree_node_t* parent = node->parent;

    create_definition(parent, array, num_of_prop);

    char* prop = (char*) calloc(MAX_STRLEN, sizeof(char));

    if (parent->right == node) {
        snprintf(prop, MAX_STRLEN, "not %s", parent->data);
        //printf("not ");
    }
    else {
        snprintf(prop, MAX_STRLEN, "%s", parent->data);
    }
    array[*num_of_prop] = prop;
    (*num_of_prop)++;

    //printf("%s\n", parent->data);
}

tree_node_t* find_user_answer_g(tree_node_t* node, Music song, int width)
{
    assert(node);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(song);
        if (node->left == NULL && node->right == NULL) {
            return node;
        }

        char* question = (char*) calloc(MAX_STRLEN, sizeof(char));
        snprintf(question, MAX_STRLEN, "Is it %s?\n", node->data);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(50, 50, 100, 100, RED);

            DrawRectangle(90, 90, 100, 100, BLUE);
            int question_length = MeasureText(question, 50);
            DrawText(question, (width - question_length) / 2, 350, 50, DARKGRAY);

            DrawRectangle(150, 600, 400, 150, BLUE);
            DrawText("YES", 300, 650, 50, DARKGRAY);

            DrawRectangle(700, 600, 400, 150, RED);
            DrawText("NO", 850, 650, 50, DARKGRAY);

        EndDrawing();

        Vector2 current_position = {};
        current_position = GetMousePosition();

        if (current_position.x > 150 && current_position.x < 550 && current_position.y > 600 && current_position.y < 750 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            node = node->left;
        }

        if (current_position.x > 700 && current_position.x < 1100 && current_position.y > 600 && current_position.y < 750 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            node = node->right;
        }

        free(question);
    }

    return node;
}

void talk_with_user_g(tree_node_t* answer, Music song, int width)
{
    assert(answer);

    FRAME type_of_frame = FRAME_QUESTION;
    float counter = 0;

    while (!WindowShouldClose())
    {
        if (counter > 2) {
            break;
        }
        UpdateMusicStream(song);
        char* question = (char*) calloc(MAX_STRLEN, sizeof(char));
        snprintf(question, MAX_STRLEN, "Did you pick the %s?\n", answer->data);

        BeginDrawing();
            ClearBackground(RAYWHITE); //
            DrawRectangle(50, 50, 100, 100, RED);
            DrawRectangle(90, 90, 100, 100, BLUE);

            if (type_of_frame == FRAME_QUESTION) {
                int question_length = MeasureText(question, 50);
                DrawText(question, (width - question_length) / 2, 350, 50, DARKGRAY);
            }
            else if (type_of_frame == FRAME_AKINATOR_WIN) {
                counter += GetFrameTime();
                const char* phrase = "Good attempt, but i win.. again";
                int phrase_length = MeasureText(phrase, 50);
                DrawText(phrase, (width - phrase_length) / 2, 350, 50, DARKGRAY);
            }

            else if (type_of_frame == FRAME_USER_WIN) {
                counter += GetFrameTime();
                const char* phrase = "I don't know this word, you win)";
                int phrase_length = MeasureText(phrase, 50);
                DrawText(phrase, (width - phrase_length) / 2, 350, 50, DARKGRAY);
            }

            DrawRectangle(150, 600, 400, 150, BLUE);
            DrawText("YES", 300, 650, 50, DARKGRAY);

            DrawRectangle(700, 600, 400, 150, RED);
            DrawText("NO", 850, 650, 50, DARKGRAY);

        EndDrawing();

        Vector2 current_position = {};
        current_position = GetMousePosition();

        if (current_position.x > 150 && current_position.x < 550 && current_position.y > 600 && current_position.y < 750 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                type_of_frame = FRAME_AKINATOR_WIN;
        }
        if (current_position.x > 700 && current_position.x < 1100 && current_position.y > 600 && current_position.y < 750 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            type_of_frame = FRAME_USER_WIN;
        }

        free(question);
    }
}

    void end_game(Music song, GAME_STATE* state)
{

    Texture2D poltorashka = LoadTexture("data/poltarashka.png");

    while (!WindowShouldClose())
    {
        UpdateMusicStream(song);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(50, 50, 100, 100, RED);
            DrawRectangle(90, 90, 100, 100, BLUE);

            DrawRectangle(70, 300, 400, 150, BLUE);
            DrawText("EXIT", 200, 350, 50, DARKGRAY);

            DrawRectangle(70, 600, 400, 150, BLUE);
            DrawText("RESTART", 150, 650, 50, DARKGRAY);

            Vector2 poltorashka_position = {500, 150};

            DrawTextureEx(poltorashka, poltorashka_position, 0, 0.4f, RAYWHITE);


            Vector2 current_position = {};
            current_position = GetMousePosition();

            if (current_position.x > 70 && current_position.x < 470 && current_position.y > 300 && current_position.y < 450 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *state = GAME_STATE_END;
                break;
            }
            else if (current_position.x > 70 && current_position.x < 470 && current_position.y > 600 && current_position.y < 750 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *state = GAME_STATE_COUNTINUE;
                break;
            }
        EndDrawing();
    }
}

void begin_game(Music song)
{
    while (!WindowShouldClose())
    {
        UpdateMusicStream(song);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(50, 50, 100, 100, RED);
            DrawRectangle(90, 90, 100, 100, BLUE);

            DrawRectangle(350, 600, 400, 150, BLUE);
            DrawText("START", 450, 650, 50, DARKGRAY);

            DrawText("Hi, i'm Akinator, let's play", 300, 300, 50, DARKGRAY);
            DrawText("Think a word connected with mathematics", 150, 370, 50, DARKGRAY);
            DrawText("I'll try to guess it, answer only YES and NO", 50, 440, 50, DARKGRAY);
            Vector2 current_position = {};
            current_position = GetMousePosition();

            if (current_position.x > 350 && current_position.x < 750 && current_position.y > 600 && current_position.y < 750 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                break;
            }
        EndDrawing();
    }
}

void compare_two_words(char* first_user_word, char* second_user_word, tree_node_t* root)
{
    tree_node_t* node_with_first_user_word = find_node(first_user_word, root);
    tree_node_t* node_with_second_user_word = find_node(second_user_word, root);

    bool is_input_correct = true;

    if (node_with_first_user_word == NULL) {
        printf("We don't have %s in our database\n", first_user_word);
        is_input_correct = false;
    }

    if (node_with_second_user_word == NULL) {
        printf("We don't have %s in our database\n", second_user_word);
        is_input_correct = false;
    }

    if (!is_input_correct) {
        return;
    }

    /* if (node_with_first_user_word == NULL && node_with_second_user_word == NULL) {
        compare_two_nodes(node_with_first_user_word, node_with_second_user_word);
    } */

    char** definition_of_first_word = (char**) calloc(MAX_NUM_OF_PROPS, sizeof(char*));
    char** definition_of_second_word = (char**) calloc(MAX_NUM_OF_PROPS, sizeof(char*));

    int num_of_prop_first = 0;

    create_definition(node_with_first_user_word, definition_of_first_word, &num_of_prop_first);
    putchar('\n');

    int num_of_prop_second = 0;
    create_definition(node_with_second_user_word, definition_of_second_word, &num_of_prop_second);
    putchar('\n');

    printf(MY_YELLOW "Common part of definitios:\n");
    printf("---------------\n");

    int i = 0;
    for (i = 0; strcmp(definition_of_first_word[i], definition_of_second_word[i]) == 0; i++) {
        printf(RESET "%s\n", definition_of_first_word[i]);
    }

    if (i == 0) {
        printf(RESET "No common part\n");
    }

    printf(MY_YELLOW "---------------\n\n");

    printf(MY_PURPLE "%s:\n", first_user_word);
    printf(MY_PURPLE "---------------\n");

    for (int first_counter = i; first_counter < num_of_prop_first; first_counter++) {
        printf(RESET "%s\n", definition_of_first_word[first_counter]);
    }

    printf(MY_PURPLE "---------------\n\n");

    printf(MY_PURPLE "%s:\n", second_user_word);
    printf(MY_PURPLE "---------------\n");

    for (int second_counter = i; second_counter < num_of_prop_second; second_counter++) {
        printf(RESET "%s\n", definition_of_second_word[second_counter]);
    }

    printf(MY_PURPLE "---------------\n");
    printf(RESET);
}


