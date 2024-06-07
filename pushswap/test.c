#include <stdio.h>
#include "pushswap.h"

void print_stack(const char* name, int* stack, int num_elements) {
    printf("%s: ", name);
    for (int i = 0; i < num_elements; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    // Create a test case
    t_push push;
    int stacka[4] = {5, 3, 7, 2}; // Example stack A
    int stackb[4] = {}; // Example empty stack B
    push.stacka = stacka;
    push.stackb = stackb;
    push.asize = 4; // Number of elements in stack A
    push.bsize = 0; // Number of elements in stack B

    // Print initial state
    printf("Initial state:\n");
    print_stack("Stack A", push.stacka, push.asize);
    print_stack("Stack B", push.stackb, push.bsize);
    printf("\n");

    // Perform a series of commands
    cmd_sa(&push, 1); // Swap the top two elements of stack A
    // cmd_pb(&push); // Push the top element of stack A onto stack B
    // cmd_pb(&push); // Push the top element of stack A onto stack B
    // cmd_rr(&push); // Rotate both stacks to the right
    // cmd_ra(&push, 1); // Rotate stack A to the right
    // cmd_rb(&push, 1); // Rotate stack B to the right
    // cmd_pb(&push); // Push the top element of stack A onto stack B
    // cmd_sa(&push, 1); // Swap the top two elements of stack A
    // cmd_rra(&push,1 ); // Reverse rotate stack A
    // cmd_rrb(&push,1 ); // Reverse rotate stack B
    // cmd_pa(&push); // Push the top element of stack B onto stack A

    // Print final state
    printf("\nFinal state:\n");
    print_stack("Stack A", push.stacka, push.asize);
    print_stack("Stack B", push.stackb, push.bsize);

    return 0;
}
