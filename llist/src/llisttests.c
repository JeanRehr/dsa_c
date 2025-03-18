#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "llist.h"

void test_create_node()
{
    Node *node = create_node(10);
    assert(node != NULL);
    assert(node->data == 10);
    assert(node->next == NULL);

    free(node);
    printf("test_create_node passed.\n");
}

void test_prepend()
{
    LList list;
    init(&list);

    prepend(&list, 10);
    assert(list.head->data == 10);
    assert(list.size == 1);
    prepend(&list, 20);
    assert(list.size == 2);
    assert(list.head->data == 20);
    assert(list.head->next->data == 10);
    prepend(&list, 30);
    assert(list.size == 3);
    assert(list.head->next->next->data == 10);
    assert(list.head->next->next->next == NULL);

    printf("test_prepend passed.\n");
    free_list(&list);
}

void test_append()
{
    LList list;
    init(&list);

    append(&list, 10);
    assert(list.size == 1);
    assert(list.head->data == 10);
    append(&list, 20);
    assert(list.size == 2);
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    append(&list, 30);
    assert(list.size == 3);
    assert(list.head->next->next->data == 30);
    assert(list.head->next->next->next == NULL);

    printf("test_append passed.\n");
    free_list(&list);
}

void test_insert_at()
{
    LList list;
    init(&list);

    insert_at(&list, 10, 0);
    assert(list.size == 1);
    assert(list.head->data == 10);
    insert_at(&list, 20, -1);
    assert(list.size == 2);
    assert(list.head->data == 20);
    assert(list.head->next->data == 10);
    insert_at(&list, 30, 10000);
    assert(list.size == 3);
    assert(list.head->next->next->data == 30);
    insert_at(&list, 40, 1);
    assert(list.size == 4);
    assert(list.head->next->next->data == 40);
    assert(list.head->next->next->next->data == 30);
    assert(list.head->next->next->next->next == NULL);

    printf("test_insert_at passed.\n");
    free_list(&list);
}

void test_insert_mixed()
{
    LList list;
    init(&list);

    prepend(&list, 10);
    append(&list, 20);
    insert_at(&list, 30, 2);
    assert(list.size == 3);
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    assert(list.head->next->next->data == 30);

    printf("test_insert_mixed passed.\n");
    free_list(&list);
}

void test_delete_head()
{
    LList list;
    init(&list);

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    assert(list.head->data == 10);
    assert(list.head->next->next->data == 30);
    assert(list.size == 3);

    delete_head(&list);
    assert(list.head->data == 20);
    assert(list.head->next->next == NULL);
    assert(list.size == 2);

    printf("test_delete_head passed.\n");
    free_list(&list);
}

void test_delete_tail()
{
    LList list;
    init(&list);

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    assert(list.head->data == 10);
    assert(list.head->next->next->data == 30);
    assert(list.size == 3);

    delete_tail(&list);
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    assert(list.head->next->next == NULL);
    assert(list.size == 2);

    printf("test_delete_tail passed.\n");
    free_list(&list);
}

void test_delete_value()
{
    LList list;
    init(&list);

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    assert(list.head->data == 10);
    assert(list.head->next->next->data == 30);
    assert(list.size == 3);

    delete_value(&list, 20);
    assert(list.head->data == 10);
    assert(list.head->next->data == 30);
    assert(list.head->next->next == NULL);
    assert(list.size == 2);

    printf("test_delete_value passed.\n");
    free_list(&list);
}

void test_delete_at()
{
    LList list;
    init(&list);

    append(&list, 10);
    append(&list, 20);
    append(&list, 30);
    append(&list, 40);
    assert(list.head->data == 10);
    assert(list.head->next->next->next->data == 40);
    assert(list.size == 4);

    delete_at(&list, 2); // delete value 30
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    assert(list.head->next->next->data == 40);\
    assert(list.head->next->next->next == NULL);
    assert(list.size == 3);

    printf("test_delete_at passed.\n");
    free_list(&list);
}

void run_all_tests()
{
    test_create_node();
    test_prepend();
    test_append();
    test_insert_at();
    test_insert_mixed();
    test_delete_head();
    test_delete_tail();
    test_delete_value();
    test_delete_at();
}

int main(void)
{
    run_all_tests();
    return 0;
}