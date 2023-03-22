#include <stdio.h>
#include <stdlib.h>

struct NodeList start_list(int data);
struct Node *append_node(struct NodeList *list, int data);
struct Node *prepend_node(struct NodeList *list, int data);
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

struct NodeList start_list(int data)
{
    struct Node *first = calloc(1, sizeof(struct Node));

    first->data = data;
    first->next = NULL;
    first->prev = NULL;

    struct NodeList ret = {
        .head = first,
        .tail = first,
    };

    return ret;
}

struct Node *append_node(struct NodeList *list, int data)
{
    struct Node *new = calloc(1, sizeof(struct Node));

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    new->prev = list->tail;
    list->tail->next = new;
    list->tail = new;

    return new;
}

struct Node *prepend_node(struct NodeList *list, int data)
{
    struct Node *new = calloc(1, sizeof(struct Node));

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    new->next = list->head;
    list->head->prev = new;
    list->head = new;

    return new;
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

    print_list(&start);
    destroy_list(&start);
    return EXIT_SUCCESS;
}
