#include <stdio.h>
#include <stdlib.h>
#include "../thirdparty/ctest.h"
#include "../src/include/s_node.h"
#include "../src/include/h_node_h_tree.h"
#include "../src/include/types.h"
#include "../src/include/vector.h"
#include "../src/include/vector_s_count.h"

size_t capacity = 10;
uint8_t symbols = 0;

CTEST(vector_init_, test_1)
{
    vector *rtrn = vector_init();
    ASSERT_NOT_NULL(rtrn);
}
CTEST(vector_push_back_, test_1)
{
    vector *v = vector_init();
    char expected = 0;
    char real = vector_push_back(v, 'a');
    ASSERT_EQUAL(expected, real);
}
CTEST(vector_s_count_init_, test_1)
{
    vector_s_count **rtrn = vector_s_count_init();
    ASSERT_NOT_NULL(rtrn);
}
CTEST(s_node_init_, test_1)
{
    uint8_t count = 10;
    s_node *s_n = s_node_itit(count);
    ASSERT_NOT_NULL(s_n);
}
CTEST(search_symbol_, test_1)
{
    s_node node = {'a', 2, 0x2, NULL, NULL, NULL};
    tree tre;
    tre.head = &node;
    char expected = -1;
    char real = search_symbol(&tre, 0x2, 2);
    ASSERT_NOT_EQUAL(expected, real);
}

CTEST(h_tree_init_, test_1)
{
    h_tree *tre = h_tree_init();
    ASSERT_NOT_NULL(tre);
}
CTEST(h_tree_node_init_, test_1)
{
    h_node *node = h_node_init('a', 3, 0);
    ASSERT_NOT_NULL(node);
}
CTEST(dequeue_min_, test_1)
{
    h_tree *tre = h_tree_init();
    h_node *node = h_node_init('a', 3, 0);
    h_tree_node_add(tre, node->s, node->weight);
    h_node *node_min = dequeue_min(tre);
    ASSERT_NOT_NULL(node_min);
}
