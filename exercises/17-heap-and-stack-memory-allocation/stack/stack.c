#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// our struct will be a string only struct
struct Stack {
    int top;
    char **strings;
};

struct Stack *Stack_create(int size) {
    struct Stack *stack = malloc(sizeof(struct Stack));
    assert(stack != NULL);
    stack->top = 0;
    stack->strings = malloc(size * sizeof(char *));
    assert(stack->strings != NULL);
    return stack;
}

void Stack_destroy(struct Stack *stack)
{
    free(stack->strings);
    free(stack);
}

void Stack_push(struct Stack *stack, char *str)
{
    stack->strings[stack->top++] = str;
}

char *Stack_pop(struct Stack *stack)
{
    return stack->strings[--stack->top];
}

char *Stack_peek(struct Stack *stack)
{
    return stack->strings[stack->top - 1];
}

int Stack_length(struct Stack *stack)
{
    return stack->top;
}

void Stack_clear(struct Stack *stack)
{
    stack->top = 0;
}

int main(int argc, char *argv[])
{
    struct Stack *stack = Stack_create(250);

    Stack_push(stack, "David");
    Stack_push(stack, "Raymond");
    Stack_push(stack, "Bryan");
    printf("length: %d\n", Stack_length(stack));
    printf("%s\n", Stack_peek(stack));
    char *popped = Stack_pop(stack);
    printf("The popped element is: %s\n", popped);
    printf("%s\n", Stack_peek(stack));
    Stack_push(stack, "Cynthia");
    printf("%s\n", Stack_peek(stack));
    Stack_clear(stack);
    printf("length: %d\n", Stack_length(stack));
    printf("%s\n", Stack_peek(stack));
    Stack_push(stack, "Clayton");
    printf("%s\n", Stack_peek(stack));

    Stack_destroy(stack);    
    return 0;
}
