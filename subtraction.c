/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	/* Definition goes here */
	int borrow = 0;
	int difference = 0;
	*headR = NULL;
	int isnegative = 0;
	if (*head1 == NULL && *head2 == NULL)
	{
		return FAILURE;
	}
	if (islengthcmp(*head1, *head2))
	{
		Dlist *temphead = *head1;
		*head1 = *head2;
		*head2 = temphead;
		Dlist *temptail = *tail1;
		*tail1 = *tail2;
		*tail2 = temptail;
		isnegative = 1;
	}
	Dlist *list1 = *tail1; // Start from the tail of the first list
	Dlist *list2 = *tail2; // Start from the tail of the second list
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
	if (isnegative)
	{
		printf("-");
	}
	printlist_for_sub(*headR); // Print the resultant list
	return SUCCESS;
}

int islengthcmp(Dlist *head1, Dlist *head2)
{
	int length1 = 0;
	int length2 = 0;
	Dlist *current1 = head1;
	Dlist *current2 = head2;
	while (current1 != NULL)
	{
		length1++;
		current1 = current1->next;
	}
	while (current2 != NULL)
	{
		length2++;
		current2 = current2->next;
	}
	if (length1 < length2)
	{
		return 1;
	}
	if (length1 > length2)
	{
		return 0;
	}
	// if lengths are equal then you should check for digits
	current1 = head1;
	current2 = head2;
	while (current1 != NULL && current2 != NULL)
	{
		if (current1->data < current2->data)
		{
			return 1;
		}
		if (current1->data > current2->data)
		{
			return 0;
		}
		current1 = current1->next;
		current2 = current2->next;
	}
	// if they are digits are equal return zero;
	return 0;
}

void printlist_for_sub(Dlist *headR)
{
	if (headR == NULL)
	{
		printf("Resultant list is empty.\n");
		return; // If the list is empty, print a message and return
	}

	Dlist *current = headR;
	int isleading_zero = 1;
	while (current != NULL)
	{
		if (current->data != 0)
		{
			isleading_zero = 0;
		}
		if (!isleading_zero || current->next == NULL)
		{
			printf("%d", current->data);
		}
		current = current->next;
	}
	current = headR;
	printf("\n");
}