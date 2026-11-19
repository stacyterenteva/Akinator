#include <stdio.h>
#include <string.h>
#include "raylib.h"

#include "../include/binary_tree.h"
#include "../include/play_funcs.h"

enum MODE
{
    MODE_PLAY = 1,
    MODE_DEF,
    MODE_DUMP,
    MODE_HELP,
    MODE_GRAPHIC_PLAY,
    MODE_COMPARING
};

MODE process_argv(char* argv[]);

int main(int argc, char* argv[])
{
    int mode = MODE_PLAY;
    if (argc != 1) { // play mode is default
        mode = process_argv(argv);
        if (mode == MODE_HELP) {
            return 0;
        }
    }

    FILE* database = fopen("data/database.txt", "r");
    tree_node_t* root = read_tree(database);
    fclose(database);

    switch (mode) {
        case MODE_PLAY: {
            tree_node_t* answer = find_user_answer(root);
            talk_with_user(answer);

            database = fopen("data/database.txt", "w");
            convert_into_text(root, database);
            fclose(database);
            break;
        }
        case MODE_DEF: {
            printf("Input word, i'll give you it's definition\n");

            char* user_word = (char*) calloc(MAX_STRLEN, sizeof(char));
            get_string(user_word, MAX_STRLEN);

            char** definition_of_user_word = (char**) calloc(MAX_NUM_OF_PROPS, sizeof(char*));
            int num_of_props = 0;

            tree_node_t* node_with_user_word = find_node(user_word, root);
            if (node_with_user_word == NULL) {
                printf("We don't have %s in our database\n", user_word);
                free(user_word);
                break;
            }
            else {
                create_definition(node_with_user_word, definition_of_user_word, &num_of_props);
            }

            for (int i = 0; i < num_of_props; i++) {
                if (i == num_of_props - 1) {
                    printf("%s", definition_of_user_word[i]);
                }
                else {
                    printf("%s, ", definition_of_user_word[i]);
                }
            }

            free(user_word);
            break;
        }
        case MODE_DUMP: {
            dump(root);
            printf("Image of database already in folder \"dump\"\n");
            break;
        }
        case MODE_GRAPHIC_PLAY: {
            const int width = 1200;
            const int height = 900;
            InitWindow(width, height, "test_window");

            InitAudioDevice();
            Music song = LoadMusicStream("data/session.mp3");
            SetMusicVolume(song, 1.0);
            PlayMusicStream(song);

            GAME_STATE state = GAME_STATE_COUNTINUE;

            begin_game(song);

            while (state != GAME_STATE_END) {
                printf("%d\n", state);

                tree_node_t* answer = find_user_answer_g(root, song, width);
                talk_with_user_g(answer, song, width);

                end_game(song, &state);
            }

            StopMusicStream(song);
            UnloadMusicStream(song);
            CloseAudioDevice();
            CloseWindow();
            break;
        }
        case MODE_COMPARING: {
            printf("Input two words, i'll compare it\n");

            char* first_user_word = (char*) calloc(MAX_STRLEN, sizeof(char));
            get_string(first_user_word, MAX_STRLEN);

            char* second_user_word = (char*) calloc(MAX_STRLEN, sizeof(char));
            get_string(second_user_word, MAX_STRLEN);

            compare_two_words(first_user_word, second_user_word, root);
            break;
        }
        default:
        printf("Unknown comand %d\n", mode);
        break;
    }

    destroy_tree(root);
    return 0;
}

MODE process_argv(char* argv[])
{
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--h") == 0) {
        printf("you can choose one of five modes\n");
        printf("1 - consol play mode\n");
        printf("2 - definitions mode\n");
        printf("3 - watch database(you can find image in folder \"dump\"\n");
        printf("4 - graphic play mode\n");
        printf("5 - comparing of two words\n");
        return MODE_HELP;
    }

    else if (strcmp("1", argv[1]) == 0) {
        return MODE_PLAY;
    }

    else if (strcmp("2", argv[1]) == 0) {
        return MODE_DEF;
    }

    else if (strcmp("3", argv[1]) == 0) {
        return MODE_DUMP;
    }

    else if (strcmp("4", argv[1]) == 0) {
        return MODE_GRAPHIC_PLAY;
    }

    else if (strcmp("5", argv[1]) == 0) {
        return MODE_COMPARING;
    }

    return MODE_PLAY;
}
