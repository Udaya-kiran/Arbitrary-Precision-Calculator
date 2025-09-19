// // /*******************************************************************************************************************************************************************
// // *Title			: Multiplication
// // *Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
// // *Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
// // *Input Parameters	: head1: Pointer to the first node of the first double linked list.
// //             : tail1: Pointer to the last node of the first double linked list.
// //             : head2: Pointer to the first node of the second double linked list.
// //             : tail2: Pointer to the last node of the second double linked list.
// //             : headR: Pointer to the first node of the resultant double linked list.
// // *Output			: Status (SUCCESS / FAILURE)
// // *******************************************************************************************************************************************************************/
#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{

	if (*head1 == NULL || *head2 == NULL)
	{
		return FAILURE;
	}

	Dlist *list1 = *tail1; // Start from the tail of the first list
	Dlist *list2 = *tail2; // Start from the tail of the second list
	int carryofproduct = 0, product;
	int zerocount = 0;

	Dlist *result1head = NULL;
	Dlist *result1tail = NULL;
	Dlist *result2head = NULL;
	Dlist *result2tail = NULL;
	Dlist *result3head = NULL;
	Dlist *result3tail = NULL;

	while (list1 != NULL)
	{
		product = (list1->data * list2->data) + carryofproduct;
		carryofproduct = product / 10;
		product = product % 10;
		insert_at_first(&result1head, &result1tail, product);
		list1 = list1->prev;
	}
	zerocount++;
	if (carryofproduct != 0)
	{
		insert_at_first(&result1head, &result1tail, carryofproduct);
	}

	list2 = list2->prev;
	while (list2 != NULL)
	{
		for (int i = 0; i < zerocount; i++)
		{
			insert_at_first(&result2head, &result2tail, 0);
		}

		list1 = *tail1;
		carryofproduct = 0;
		while (list1 != NULL)
		{
			product = (list1->data * list2->data) + carryofproduct;

			carryofproduct = product / 10; // Update carry for next iteration
			product = product % 10;
			insert_at_first(&result2head, &result2tail, product);

			list1 = list1->prev;
		}
		if (carryofproduct != 0)
		{
			insert_at_first(&result2head, &result2tail, carryofproduct);
		}

		addition_for_multiplication(&result1head, &result1tail, &result2head, &result2tail, &result3head, &result3tail);
		free_the_node(&result1head, &result1tail);
		free_the_node(&result2head, &result2tail);
		list1 = result3tail;
		while (list1 != NULL)
		{
			insert_at_first(&result1head, &result1tail, list1->data);
			list1 = list1->prev;
		}

		free_the_node(&result3head, &result3tail);
		zerocount++;
		list2 = list2->prev;
	}

	list1 = result1tail;
	while (list1 != NULL)
	{
		insert_at_first(headR, tailR, list1->data);
		list1 = list1->prev;
	}

	free_the_node(&result1head, &result1tail);

	return SUCCESS;
}

// freeing the node
int free_the_node(Dlist **resulthead, Dlist **resulttail)
{

	if (*resulthead == NULL)
	{
		return SUCCESS;
	}

	Dlist *current = *resulthead;
	Dlist *temp;

	// Traverse the list and free each node
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}

	// After the loop, the list is empty, so set both head and tail to NULL
	*resulthead = NULL;
	*resulttail = NULL;

	return SUCCESS;
}

void insert_at_first(Dlist **head, Dlist **tail, int data)
{
	Dlist *newNode = malloc(sizeof(Dlist));
	if (newNode == NULL)
	{
		printf("Failed to insert\n");
		return;
	}
	else
	{
		newNode->prev = NULL;
		newNode->data = data;
		newNode->next = NULL;
		if (*head == NULL)
		{
			*head = newNode;
			*tail = newNode;
		}
		else
		{
			newNode->next = *head;
			(*head)->prev = newNode;
			*head = newNode;
		}
	}
}

int addition_for_multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
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
		int num1 = (list1 != NULL) ? list1->data : 0;
		int num2 = (list2 != NULL) ? list2->data : 0;

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

		if (*headR == NULL)
		{

			*headR = newNode;
			*tailR = newNode;
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
