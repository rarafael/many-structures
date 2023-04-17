#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Tree *new_tree(int weight);
struct Tree *balance(struct Tree *root);
void append_tree(struct Tree *root, int weight);
void delete_tree(struct Tree *root);

struct Tree {
    int weight;
    struct Tree *right;
    struct Tree *left;
};

struct Tree *new_tree(int weight)
{
    struct Tree *ret = malloc(1 * sizeof(struct Tree));

    ret->weight = weight;
    ret->right = NULL;
    ret->left = NULL;

    return ret;
}

static int get_node_difference(struct Tree *root)
{
    struct Tree *tmp = root;
    int right_nodes = 0;
    while(tmp->right) {
        right_nodes++;
        tmp = tmp->right;
    }

    tmp = root;
    int left_nodes = 0;
    while(tmp->left) {
        left_nodes++;
        tmp = tmp->left;
    }

    return right_nodes - left_nodes;
}

struct Tree *balance(struct Tree *root)
{
    int node_difference = get_node_difference(root);
    struct Tree *new_root = root;

    if(node_difference > 0) {
        node_difference /= 2;
        while(new_root->right && (node_difference--))
            new_root = new_root->right;
        if(new_root->left)
            root->right = new_root->left;
        else
            root->right = NULL;
        new_root->left = root;
    } else if(node_difference < 0) {
        node_difference /= 2;
        while(new_root->left && (node_difference++))
            new_root = new_root->left;
        if(new_root->right)
            root->left = new_root->right;
        else
            root->left = NULL;
        new_root->right = root;
    }

    return new_root;
}

void append_tree(struct Tree *root, int weight)
{
    assert(weight != root->weight);

    if(weight > root->weight) {
        if(!root->right)
            root->right = new_tree(weight);
        else
            append_tree(root->right, weight);
    }

    if(weight < root->weight) {
        if(!root->left)
            root->left = new_tree(weight);
        else
            append_tree(root->left, weight);
    }
}

void delete_tree(struct Tree *root)
{
    if(root->right)
        delete_tree(root->right);
    if(root->left)
        delete_tree(root->left);
    free(root);
}

void print_tree(struct Tree *root)
{
    if(!root)
        return;
    printf("%d\n", root->weight);
    print_tree(root->left);
    print_tree(root->right);
}

int main(void)
{
    struct Tree *rt = new_tree(1 << 1);
    append_tree(rt, 1 << 2);
    append_tree(rt, 1 << 3);
    append_tree(rt, 1 << 4);
    struct Tree *new_rt = balance(rt);
    print_tree(new_rt);
    delete_tree(rt);
    return EXIT_SUCCESS;
}
