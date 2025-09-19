// // // /*******************************************************************************************************************************************************************
// // // *Title			: Division
// // // *Description		: This function performs division of two given large numbers and store the result in the resultant list.
// // // *Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
// // // *Input Parameters	: head1: Pointer to the first node of the first double linked list.
// // // 			: tail1: Pointer to the last node of the first double linked list.
// // // 			: head2: Pointer to the first node of the second double linked list.
// // // 			: tail2: Pointer to the last node of the second double linked list.
// // // 			: headR: Pointer to the first node of the resultant double linked list.
// // // *Output			: Status (SUCCESS / FAILURE)
// // // *******************************************************************************************************************************************************************/
#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    if (*head1 == NULL || *head2 == NULL)
    {
        return FAILURE;
    }
    *headR = NULL;
    Dlist *tailR = NULL;

    if ((*head2)->data == 0)
    {
        printf("Division by zero is not allowed\n");
        return FAILURE; // Division by zero
    }

    Dlist *list1 = *head1;
    Dlist *list2 = *head2;

    Dlist *remainder_head = NULL, *remainder_tail = NULL; // To store the current remainder as a list
    int quotient_digit = 0;
    if (compare_lists(*head1, *head2) == -1)
    {
        insert_at_last(headR, &tailR, 0);
        return SUCCESS;
    }
    else
    {
        if (*head1 != NULL)
        {
            while (compare_lists(*head1, *head2) >= 0)
            {

                subtract_lists(head1, tail1, head2, tail2, &remainder_head, &remainder_tail);
                Dlist *temp = *head1;
                while (temp)
                {
                    *head1 = temp->next;
                    free(temp);
                    temp = *head1;
                }
                *tail1 = NULL;
                temp = remainder_head;
                *head1 = remainder_head;
                *tail1 = remainder_tail;
                remainder_head = remainder_tail = NULL;
                quotient_digit++;
            }
        }
    }
    insert_at_last(headR, &tailR, quotient_digit);
    Dlist *temp = *headR;
    while (temp != NULL && temp->data == 0)
    {
        temp = temp->next;
    }
    *headR = temp;

    if (*headR == NULL)
    {
        insert_at_last(headR, &tailR, 0);
    }

    return SUCCESS;
}

int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
    {
        return FAILURE;
    }
    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    if (*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;
    return SUCCESS;
}

int compare_lists(Dlist *head1, Dlist *head2)
{
    // Remove leading zeroes
    while (head1 != NULL && head1->data == 0)
    {
        head1 = head1->next;
    }
    while (head2 != NULL && head2->data == 0)
    {
        head2 = head2->next;
    }

    // Compare lengths
    int len1 = 0, len2 = 0;
    Dlist *temp1 = head1, *temp2 = head2;
    while (temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    if (len1 > len2)
        return 1; // head1 is larger
    if (len1 < len2)
        return -1; // head2 is larger

    // If lengths are the same, compare digit by digit
    while (head1 != NULL)
    {
        if (head1->data > head2->data)
            return 1;
        if (head1->data < head2->data)
            return -1;
        head1 = head1->next;
        head2 = head2->next;
    }

    return 0; // Both are equal
}

int subtract_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Definition goes here */
    int borrow = 0;
    int difference = 0;
    *headR = NULL;
    if (*head1 == NULL && *head2 == NULL)
    {
        return FAILURE;
    }

    Dlist *list1 = *tail1;
    Dlist *list2 = *tail2;
    while (list1 != NULL || list2 != NULL || borrow != 0)
    {
        difference = 0;
        int num1 = (list1 != NULL) ? list1->data : 0;
        int num2 = (list2 != NULL) ? list2->data : 0;

        if (borrow)
        {
            num1 -= 1;
            borrow = 0;
        }
        if (num1 < num2)
        {
            num1 = num1 + 10;
            borrow = 1;
        }
        difference = num1 - num2;
        Dlist *new = malloc(sizeof(Dlist));
        if (new == NULL)
        {
            return FAILURE;
        }
        new->data = difference;
        new->prev = NULL;
        new->next = NULL;
        if (*headR == NULL)
        {
            *headR = new;
            *tailR = new;
        }
        else
        {
            new->next = *headR;
            (*headR)->prev = new;
            *headR = new;
        }
        if (list1 != NULL)
        {
            list1 = list1->prev;
        }
        if (list2 != NULL)
        {
            list2 = list2->prev;
        }
    }
    Dlist *temp = *headR;
    while (temp != NULL && temp->data == 0)
    {
        temp = temp->next;
    }
    *headR = temp;

    return SUCCESS;
}