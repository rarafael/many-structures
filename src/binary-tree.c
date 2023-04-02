#include <stdio.h>
#include <stdlib.h>

struct Tree *new_tree(int data);
void append_tree(struct Tree *tree, int data, int side);
void remove_tree(struct Tree *root, struct Tree *removal);
void print_tree(struct Tree *root);
void delete_tree(struct Tree *tree);

#define RIGHT   0
#define LEFT    1

struct Tree {
    int data;
    struct Tree *right;
    struct Tree *left;
};

struct Tree *new_tree(int data)
{
    struct Tree *ret = malloc(1 * sizeof(struct Tree));

    ret->data = data;
    ret->right = NULL;
    ret->left = NULL;

    return ret;
}

void append_tree(struct Tree *tree, int data, int side)
{
    if(side)
        tree->left = new_tree(data);
    else
        tree->right = new_tree(data);
}

void remove_tree(struct Tree *root, struct Tree *removal)
{
    if(root->right != NULL) {
        if(root->right == removal) {
            if(removal->right == NULL && removal->left == NULL)
                root->right = NULL;
            if(removal->right == NULL && removal->left != NULL) {
                root->right = removal->left;
                free(removal);
            }

            else {
                root->right = removal->right;
                free(removal);
            }
        } else
            remove_tree(root->right, removal);
    }

    if(root->left != NULL) {
        if(root->left == removal) {
            if(removal->right == NULL && removal->left == NULL)
                root->left = NULL;
            if(removal->right == NULL && removal->left != NULL) {
                root->left = removal->left;
                free(removal);
            }

            else {
                root->left = removal->right;
                free(removal);
            }
        } else
            remove_tree(root->left, removal);
    }
}

void print_tree(struct Tree *root)
{
    printf("%d\n", root->data);

    if(root->right != NULL) {
        printf("r: ");
        print_tree(root->right);
    }

    if(root->left != NULL) {
        printf("l: ");
        print_tree(root->left);
    }
}

void delete_tree(struct Tree *tree)
{
    if(!tree)
        return;
    delete_tree(tree->left);
    delete_tree(tree->right);
    free(tree);
}

int main(void)
{
    struct Tree *root = new_tree(1 << 1);
    append_tree(root, 1 << 2, RIGHT);
    append_tree(root, 1 << 3, LEFT);
    append_tree(root->right, 1 << 4, RIGHT);
    append_tree(root->left, 1 << 5, RIGHT);
    print_tree(root);
    delete_tree(root);
    return 0;
}
