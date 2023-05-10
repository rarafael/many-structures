#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int *value;
    size_t len;
};

void free_stack(struct Stack *stack);
struct Stack new_stack(int value);
void push(int value, struct Stack *stack);
int pop(struct Stack *stack);
void print(struct Stack stack);

struct Stack new_stack(int value)
{
    struct Stack ret = {0};

    ret.value = calloc(1, sizeof(int));
    ret.len = 1;
    ret.value[0] = value;

    return ret;
}

void push(int value, struct Stack *stack)
{
    stack->len += 1;
    stack->value = realloc(stack->value, stack->len);
    stack->value[stack->len - 1] = value;
}

int pop(struct Stack *stack)
{
    assert(stack);
    int ret = stack->value[stack->len - 1];
    stack->len -= 1;
    if(!stack->len)
        free_stack(stack);
    else
        stack->value = realloc(stack->value, stack->len);
    return ret;
}

void free_stack(struct Stack *stack)
{
    free(stack->value);
    stack->len = 0;
    stack->value = NULL;
}

void print(struct Stack stack)
{
    for(size_t i = 0; i < stack.len; i++) {
        printf("%d\n", stack.value[i]);
    }
}

int main(void)
{
    struct Stack h = new_stack(1 << 1);
    push(1 << 2, &h);
    push(1 << 3, &h);
    print(h);
    printf("%d\n", pop(&h));
    print(h);
    free_stack(&h);
    return EXIT_SUCCESS;
}
