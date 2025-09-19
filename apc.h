#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
} Dlist;

/* Include the prototypes here */

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

int read_and_validate(int argc, char *argv[]);

int creatNode(Dlist **head, Dlist **tail, int data);

void stringToLinkedlist(Dlist **head, Dlist **tail, const char *argv);

void printlist(Dlist *headR);

void printlist_for_sub(Dlist *headR);

void clear_result_list(Dlist **head);

int islengthcmp(Dlist *head1, Dlist *head2);

int free_the_node(Dlist **resulthead, Dlist **resulttail);

void insert_at_first(Dlist **head, Dlist **tail, int data);

void dl_insert_last(Dlist **head, Dlist **tail, int data);

int addition_for_multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int insert_at_last(Dlist **head, Dlist **tail, int data);

Dlist *create_node(int data);

int compare_lists(Dlist *head1, Dlist *head2);

int subtract_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **);

#endif
