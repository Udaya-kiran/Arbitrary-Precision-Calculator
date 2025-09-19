/**************************************************************************************************************************************************************
 * Name : uday  kiran n u
 * Date : 20-11-2024
 * Project Description : Arbitrary Precision Calculator
 *Title		: main function(Driver function)
 *Description	: This function is used as the driver function for the all the functions
 ***************************************************************************************************************************************************************/
#include "apc.h"

int main(int argc, char *argv[])
{
    /* Declare the pointers */
    Dlist *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;
    char option, operator;
    int sign1 = 1, sign2 = 1; // 1 for positive, -1 for negative
    int flag = 0;             // To determine if the result should be negative (for multiplication and division)
    int high;

    // Check if correct number of arguments
    if (argc == 4)
    {
        if (read_and_validate(argc, argv) == FAILURE)
        {
            printf("INVALID ARGUMENTS\n");
            printf("Usage : -> ./a.out <number1> <operator> <number2>\n");
        }
        else
        {
            // Handle the sign of the first operand (argv[1])
            if (argv[1][0] == '-' || argv[1][0] == '+')
            {
                if (argv[1][0] == '-')
                    sign1 = -1; // Operand 1 is negative
                argv[1]++;      // Remove the sign for processing the number
            }

            // Handle the sign of the second operand (argv[3])
            if (argv[3][0] == '-' || argv[3][0] == '+')
            {
                if (argv[3][0] == '-')
                    sign2 = -1; // Operand 2 is negative
                argv[3]++;      // Remove the sign for processing the number
            }

            // Convert the numbers (strings) to linked lists (ignoring the signs)
            stringToLinkedlist(&head1, &tail1, argv[1]);
            stringToLinkedlist(&head2, &tail2, argv[3]);

            // Extract the operator
            operator= argv[2][0];
                
            // Modify the operator based on signs:
            if (sign1 == -1 && sign2 == -1 && operator== '-')
            {
                // Both operands are negative, subtracting negative -> add positive
                operator= '+';
            }
            else if (sign1 == -1 && operator== '-')
            {
                // Operand 1 is negative and operator is '-', change to addition
                operator= '+';
                sign1 = 1; // Treat it as a positive operand after sign handling
            }
            else if (sign2 == -1 && operator== '-')
            {
                // Operand 2 is negative and operator is '-', change to addition
                operator= '+';
                sign2 = 1; // Treat it as a positive operand after sign handling
            }


               
            // Perform the requested operation
            do
            {
                clear_result_list(&headR); // Clear the result list for the next operation

                switch (operator)
                {
                case '+':
                    addition(&head1, &tail1, &head2, &tail2, &headR);
                    break;
                case '-':
                    subtraction(&head1, &tail1, &head2, &tail2, &headR);
                    break;
                case 'x':
                    multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                    break;
                case '/':
                    division(&head1, &tail1, &head2, &tail2, &headR);
                    break;
                default:
                    printf("Invalid Input:-( Try again...\n");
                    continue;
                }
                   


                   if (operator == '-')
{
    // Case when both operands are negative:
    if (sign1 == -1 && sign2 == -1)
    {
        // (-a) - (-b) -> -a + b (this is handled by subtraction logic)
        // Example: (-2) + (-5) -> -7
        // No need to change the operator here, treat it normally
    }
    // Case when the first operand is negative:
    else if (sign1 == -1)
    {
        // (-a) - b -> -(a + b)
        sign1 = 1; // Treat operand 1 as positive for calculation
        operator = '+'; // Change to addition
    }
    // Case when the second operand is negative:
    else if (sign2 == -1)
    {
        // a - (-b) -> a + b
        sign2 = 1; // Treat operand 2 as positive for calculation
        operator = '+'; // Change to addition
    }
}





                // Handle the sign for multiplication and division
                if (operator== 'x' || operator== '/')
                {
                    if (sign1 != sign2)
                    {
                        flag = 1; // If signs differ, result should be negative
                    }
                }

                // Apply negative sign if necessary for multiplication or division
                if (flag)
                {
                    printf("-");
                }

                if (operator!= '-')
                {
                    printlist(headR);
                }

                printf("Want to continue? Press [yY | nN]: ");
                scanf("\n%c", &option);

                if (option == 'y' || option == 'Y')
                {

                    scanf("%s %s %s %s", argv[0], argv[1], argv[2], argv[3]);
                    clear_result_list(&head1);
                    clear_result_list(&head2);
                    stringToLinkedlist(&head1, &tail1, argv[1]);
                    stringToLinkedlist(&head2, &tail2, argv[3]);
                    operator= argv[2][0];

                    sign1 = 1;
                    sign2 = 1;
                    if (argv[1][0] == '-' || argv[1][0] == '+')
                    {
                        if (argv[1][0] == '-')
                            sign1 = -1;
                        argv[1]++;
                    }
                    if (argv[3][0] == '-' || argv[3][0] == '+')
                    {
                        if (argv[3][0] == '-')
                            sign2 = -1;
                        argv[3]++;
                    }

                    if (sign1 == -1 && sign2 == -1 && operator== '-')
                    {
                        operator= '+';
                    }
                    else if (sign1 == -1 && operator== '-')
                    {
                        operator= '+';
                        sign1 = 1;
                    }
                    else if (sign2 == -1 && operator== '-')
                    {
                        operator= '+';
                        sign2 = 1;
                    }
                }
            } while (option == 'y' || option == 'Y');
        }
    }
    else
    {
        printf("INVALID ARGUMENTS\n");
        printf("Usage : -> ./a.out <number1> <operator> <number2>\n");
    }
    return 0;
}
