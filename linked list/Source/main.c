#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "D:\code\linked list\Header\linkedlist.h"
#include "D:\code\linked list\Source\linkedlist.c"


int main(int argc, char const *argv[])
{
    node *array = NULL;
    printf(" test empty %d\n",empty(array));
    push_back(&array, 8);
    push_back(&array, 3);
    push_back(&array, 4);
    push_back(&array, 7);
    push_back(&array, 9);
    printf("test %d\n", length(array));
    insert(&array ,677 ,5);
    pop_back(&array);
    erase(&array,1);
    printf("test %d\n", duyet(array, 0));
    return 0;
}
