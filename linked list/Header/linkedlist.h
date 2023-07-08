#ifndef LINKEDLIST
#define LINKEDLIST
#include <stdbool.h>
/*
* File: linkedlist.h
* Author: Khuat Duc Duy
* Date: 08/07/2023
* Description: This is a file include everything in preprocessor for linkedlist.c
*/
typedef struct node
{
    int value;
    struct node *next;
} node;

node *createNode(int value);
void push_back(node **array, int value);
int length(node *array);
int duyet(node *array, int index);
void insert(node **array, int value, int pos);
void erase(node **array, int pos);
bool empty(node *array);
void pop_back(node **array);

#endif