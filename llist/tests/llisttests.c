#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "llist.h"

void test_llist_prepend()
{
    LList list;
    llist_init(&list);

    llist_prepend(&list, 10);
    assert(list.head->data == 10);
    assert(list.size == 1);
    llist_prepend(&list, 20);
    assert(list.size == 2);
    assert(list.head->data == 20);
    assert(list.head->next->data == 10);
    llist_prepend(&list, 30);
    assert(list.size == 3);
    assert(list.head->next->next->data == 10);
    assert(list.head->next->next->next == NULL);

    printf("test_llist_prepend passed.\n");
    llist_deinit(&list);
}

void test_llist_append()
{
    LList list;
    llist_init(&list);

    llist_append(&list, 10);
    assert(list.size == 1);
    assert(list.head->data == 10);
    llist_append(&list, 20);
    assert(list.size == 2);
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    llist_append(&list, 30);
    assert(list.size == 3);
    assert(list.head->next->next->data == 30);
    assert(list.head->next->next->next == NULL);

    printf("test_llist_append passed.\n");
    llist_deinit(&list);
}

void test_llist_insert_at()
{
    LList list;
    llist_init(&list);

    llist_insert_at(&list, 10, 0);
    assert(list.size == 1);
    assert(list.head->data == 10);
    llist_insert_at(&list, 20, -1);
    assert(list.size == 2);
    assert(list.head->data == 20);
    assert(list.head->next->data == 10);
    llist_insert_at(&list, 30, 10000);
    assert(list.size == 3);
    assert(list.head->next->next->data == 30);
    llist_insert_at(&list, 40, 1);
    assert(list.size == 4);
    assert(list.head->next->next->data == 40);
    assert(list.head->next->next->next->data == 30);
    assert(list.head->next->next->next->next == NULL);

    printf("test_llist_insert_at passed.\n");
    llist_deinit(&list);
}

void test_insert_mixed()
{
    LList list;
    llist_init(&list);

    llist_prepend(&list, 10);
    llist_append(&list, 20);
    llist_insert_at(&list, 30, 2);
    assert(list.size == 3);
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    assert(list.head->next->next->data == 30);

    printf("test_insert_mixed passed.\n");
    llist_deinit(&list);
}

void test_llist_delete_head()
{
    LList list;
    llist_init(&list);

    llist_append(&list, 10);
    llist_append(&list, 20);
    llist_append(&list, 30);
    assert(list.head->data == 10);
    assert(list.head->next->next->data == 30);
    assert(list.size == 3);

    llist_delete_head(&list);
    assert(list.head->data == 20);
    assert(list.head->next->next == NULL);
    assert(list.size == 2);

    printf("test_llist_delete_head passed.\n");
    llist_deinit(&list);
}

void test_llist_delete_tail()
{
    LList list;
    llist_init(&list);

    llist_append(&list, 10);
    llist_append(&list, 20);
    llist_append(&list, 30);
    assert(list.head->data == 10);
    assert(list.head->next->next->data == 30);
    assert(list.size == 3);

    llist_delete_tail(&list);
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    assert(list.head->next->next == NULL);
    assert(list.size == 2);

    printf("test_llist_delete_tail passed.\n");
    llist_deinit(&list);
}

void test_llist_delete_value()
{
    LList list;
    llist_init(&list);

    llist_append(&list, 10);
    llist_append(&list, 20);
    llist_append(&list, 30);
    assert(list.head->data == 10);
    assert(list.head->next->next->data == 30);
    assert(list.size == 3);

    llist_delete_value(&list, 20);
    assert(list.head->data == 10);
    assert(list.head->next->data == 30);
    assert(list.head->next->next == NULL);
    assert(list.size == 2);

    printf("test_llist_delete_value passed.\n");
    llist_deinit(&list);
}

void test_llist_delete_at()
{
    LList list;
    llist_init(&list);

    llist_append(&list, 10);
    llist_append(&list, 20);
    llist_append(&list, 30);
    llist_append(&list, 40);
    assert(list.head->data == 10);
    assert(list.head->next->next->next->data == 40);
    assert(list.size == 4);

    llist_delete_at(&list, 2); // delete value 30
    assert(list.head->data == 10);
    assert(list.head->next->data == 20);
    assert(list.head->next->next->data == 40);\
    assert(list.head->next->next->next == NULL);
    assert(list.size == 3);

    printf("test_llist_delete_at passed.\n");
    llist_deinit(&list);
}

void test_llist_print()
{
    LList list;
    llist_init(&list);

    printf("Adding 10.\n");
    llist_append(&list, 10);
    printf("Adding 20.\n");
    llist_append(&list, 20);
    printf("Adding 30.\n");
    llist_append(&list, 30);
    printf("Printing list:\n");
    llist_print(&list);

    printf("test_llist_print passed.\n");
    llist_deinit(&list);
}

void run_all_tests()
{
    test_llist_prepend();
    test_llist_append();
    test_llist_insert_at();
    test_insert_mixed();
    test_llist_delete_head();
    test_llist_delete_tail();
    test_llist_delete_value();
    test_llist_delete_at();
    test_llist_print();
}

int main(void)
{
    run_all_tests();
    return 0;
}