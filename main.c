#include <stdio.h>

#include <stdio.h>

#include "binary_tree.h"
#include "play_funcs.h"

int main()
{
    FILE* test_test = fopen("test_test.txt", "r");

    tree_node_t* test_test_root = read_tree(test_test);
    fclose(test_test);

    dump(test_test_root);

    tree_node_t* answer = find_user_answer(test_test_root);

    talk_with_user(answer);

    test_test = fopen("test_test.txt", "w");
    convert_into_text(test_test_root, test_test);

    fclose(test_test);
    dump(test_test_root);
}
