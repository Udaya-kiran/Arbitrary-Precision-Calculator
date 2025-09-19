#ifndef FUNCDEF_C
#define FUNCDEF_C

#include "apc.h"

int read_and_validate(int argc, char *argv[])
{
    // Validate first number (argv[1])
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]) && !(i == 0 && (argv[1][i] == '+' || argv[1][i] == '-')))
        {
            return FAILURE;
        }
    }

    // Validate operator (argv[2])
    if (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != '/')
    {
        return FAILURE;
    }

    // Validate second number (argv[3])
    for (int i = 0; argv[3][i] != '\0'; i++)
    {
        if (!isdigit(argv[3][i]) && !(i == 0 && (argv[3][i] == '+' || argv[3][i] == '-')))
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

int creatNode(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
    {
        return FAILURE;
    }
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    Dlist *temp = *tail;
    new->prev = temp;
    temp->next = new;
    *tail = new;
    return SUCCESS;
}

void stringToLinkedlist(Dlist **head, Dlist **tail, const char *argv)
{
    int flag = 0;
    for (int i = 0; argv[i] != '\0'; i++)
    {
        int digit = argv[i] - '0';
        creatNode(head, tail, digit);
    }
}

void printlist(Dlist *headR)
{
    if (headR == NULL)
    {
        printf("Resultant list is empty.\n");
        return;
    }
    Dlist *current = headR;
    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    current = headR;
    printf("\n");
}

void clear_result_list(Dlist **headR)
{
    if (*headR != NULL)
    {
        Dlist *current = *headR;
        while (current != NULL)
        {
            Dlist *nextNode = current->next;
            free(current);
            current = nextNode;
        }
        *headR = NULL;
    }
}
#endif