#include <stdio.h>
#include <stdlib.h>

struct Node *start_list(int data);
void destroy_list(struct Node *head);
struct Node *append_node(struct Node *head, int data);
void remove_node(struct Node *head, struct Node *target);
void print_list(struct Node *head);

struct Node {
    int data;
    struct Node *next;
};

struct Node *start_list(int data)
{
    struct Node *ret = calloc(1, sizeof(struct Node));

    ret->data = data;
    ret->next = NULL;

    return ret;
}

struct Node *append_node(struct Node *head, int data)
{
    struct Node *new = calloc(1, sizeof(struct Node));

    new->data = data;
    new->next = NULL;

    struct Node *tmp = head;
    while(tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = new;

    return new;
}

struct Node *prepend_node(struct Node *head, int data)
{
    struct Node *new = calloc(1, sizeof(struct Node));

    new->data = data;
    new->next = head;

    return new;
}

void remove_node(struct Node *head, struct Node *target)
{
    struct Node *tmp = head;
    if(tmp == target && !(tmp->next))
        destroy_list(tmp);

    while(tmp != NULL) {
        if(tmp->next == target) {
            if(target->next != NULL)
                tmp->next = target->next;
            else
                tmp->next = NULL;

            free(target);
            return;
        }
        tmp = tmp->next;
    }
}

void destroy_list(struct Node *head)
{
    struct Node *tmp = head;
    struct Node *nxt = head;

    do {
        tmp = nxt;
        nxt = nxt->next;
        free(tmp);
    } while(nxt);
}

void print_list(struct Node *head)
{
    struct Node *tmp = head;

    do {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    } while(tmp);
}

int main(void)
{
    struct Node *header = start_list(1 << 1);
    struct Node *n1 = append_node(header, 1 << 2);
    struct Node *new_head = prepend_node(header, 1 << 3);
    printf("%p\n", find_by_value(new_head, 1 << 2));
    print_list(new_head);
    print_list(header);
    remove_node(new_head, n1);
    destroy_list(new_head);
    return EXIT_SUCCESS;
}
