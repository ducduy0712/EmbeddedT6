#include "D:\code\linked list\Header\linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

node *createNode(int value)
{
    node *ptr = (node *)malloc(sizeof(node));
    ptr->value = value;
    ptr->next = NULL;
    return ptr;
}

void push_back(node **array, int value)
{
    node *temp, *p;
    temp = createNode(value);
    if (*array == NULL)
    {
        *array = temp;
    }
    else
    {
        p = *array;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = temp;
    }
}
int length(node *array)
{
    int i = 0;
    while (array != NULL)
    {
        i++;
        array = array->next;
    }
    return i;
}
int duyet(node *array, int index)
{
    int i = 0;
    int k = length(array);
    if (index <= k)
    {
        while (array->next != NULL && index != i)
        {
            array = array->next;
            i++;
        }
        return array->value;
    }
    else
    {
        return 0;
    };
}

void insert(node **array, int value, int pos)
{
    node *temp, *p;
    temp = createNode(value);
    p = *array;
    int i = 1;
    if (pos == 0)
    {
        temp->next = *array;
        *array = temp;
    }
    else
    {
        while (p->next != NULL && pos != i)
        {
            p = p->next;
            i++;
        }
        temp->next = p->next;
        p->next = temp;
    }
}

void erase(node **array, int pos)
{
    node *temp;
    node *tam;
    int i = 1;
    temp = *array;
    if (pos == 0)
    {
        tam = temp->next;
        *array = tam;
        free(temp);
    }

    while (temp->next != NULL && pos != i)
    {
        temp = temp->next;
        i++;
    }
    tam = temp->next;
    temp->next = tam->next;
    free(tam);
}

bool empty(node *array)
{
    if (array == NULL)
    {
        return true;
    }
    return false;
}

void pop_back(node **array)
{
    node *temp = *array;
    int i = 2;
    int k = length(*array);

    while (temp->next != NULL && i != k)
    {
        temp = temp->next;
        i++;
    }
    free(temp->next);
    temp->next = NULL;
}