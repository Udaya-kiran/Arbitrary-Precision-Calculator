/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	if (head1 == NULL && head2 == NULL)
	{
		return FAILURE;
	}
	Dlist *list1 = *tail1; // Start from the tail of the first list
	Dlist *list2 = *tail2; // Start from the tail of the second list
	int carry = 0;
	int sum = 0;
	*headR = NULL;

	//*headR = NULL; // Reset headR
	while (list1 != NULL || list2 != NULL || carry != 0)
	{
		sum = 0;
		int num1 = (list1 != NULL) ? list1->data : 0; // Get value from list1
		int num2 = (list2 != NULL) ? list2->data : 0; // Get value from list2

		// Calculate the sum for this iteration
		sum = num1 + num2 + carry;
		carry = sum / 10;

		// Create a new node for the result
		Dlist *newNode = (Dlist *)malloc(sizeof(Dlist));
		if (newNode == NULL)
		{
			return FAILURE;
		}
		newNode->data = sum % 10;
		newNode->next = NULL;
		newNode->prev = NULL;
		Dlist *tailR = NULL;
		if (*headR == NULL)
		{

			*headR = newNode;
			tailR = newNode;
		}
		else
		{

			(*headR)->prev = newNode;
			newNode->next = *headR;
			*headR = newNode;
		}

		if (list1 != NULL)
			list1 = list1->prev;
		if (list2 != NULL)
			list2 = list2->prev;
	}

	return SUCCESS;
}
