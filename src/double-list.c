#include <stdio.h>
#include <stdlib.h>

struct NodeList start_list(int data);
struct Node *append_node(struct NodeList *list, int data);
struct Node *prepend_node(struct NodeList *list, int data);
struct Node *after_node(struct Node *after, int data);
struct Node *before_node(struct Node *before, int data);
void remove_node(struct Node *removal);
void destroy_list(struct NodeList *list);
void print_list(struct NodeList *list);

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct NodeList {
    struct Node *head;
    struct Node *tail;
};

static inline struct Node *new_node(int data)
{
    struct Node *new = calloc(1, sizeof(struct Node));

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    return new;
}

struct NodeList start_list(int data)
{
    struct Node *first = new_node(data);

    struct NodeList ret = {
        .head = first,
        .tail = first,
    };

    return ret;
}

struct Node *append_node(struct NodeList *list, int data)
{
    struct Node *new = new_node(data);

    new->prev = list->tail;
    list->tail->next = new;
    list->tail = new;

    return new;
}

struct Node *prepend_node(struct NodeList *list, int data)
{
    struct Node *new = new_node(data);

    new->next = list->head;
    list->head->prev = new;
    list->head = new;

    return new;
}

struct Node *after_node(struct Node *after, int data)
{
    struct Node *new = new_node(data);

    new->next = after->next;

    if(after->next)
        after->next->prev = new;

    after->next = new;
    new->prev = after; 

    return new;
}

struct Node *before_node(struct Node *before, int data)
{
    struct Node *new = new_node(data);

    new->next = before;

    if(before->prev)
        before->prev->next = new;

    new->prev = before->prev;
    before->prev = new;

    return new;
}

void remove_node(struct Node *removal)
{
    if(removal->prev)
        removal->prev->next = removal->next;
    if(removal->next)
        removal->next->prev = removal->prev;
    free(removal);
    return;
}

void destroy_list(struct NodeList *list)
{
    struct Node *tmp = list->head;
    
    do {
        struct Node *buf = tmp->next;
        free(tmp);
        tmp = buf;
    } while(tmp);
}

void print_list(struct NodeList *list)
{
    struct Node *tmp = list->head;

    do {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    } while(tmp);
}

int main(void)
{
    struct NodeList start = start_list(1 << 1);
    struct Node *n2 = append_node(&start, 1 << 2);
    struct Node *n3 = prepend_node(&start, 1 << 3);
    struct Node *n4 = after_node(n2, 1 << 4);
    struct Node *n5 = before_node(n2, 1 << 5);

    print_list(&start);
    destroy_list(&start);
    return EXIT_SUCCESS;
}
