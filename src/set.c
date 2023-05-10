#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX(A, B) (A > B ? A : B)

struct Set {
    int *data;
    size_t size;
};

struct Set create_set(const size_t n, ...);
void free_set(struct Set *s);
bool is_element_of(int i, struct Set s);
int iterate(struct Set s, int *iter);
int *enumerate(struct Set s);
size_t size(struct Set s);
struct Set union_set(struct Set s1, struct Set s2);
struct Set difference(struct Set s1, struct Set s2);
void print_set(struct Set s);

struct Set create_set(const size_t n, ...)
{
    struct Set ret = {0};
    ret.size = n;
    ret.data = calloc(n, sizeof(int));

    va_list ap;
    va_start(ap, n);

    for(size_t i = 0; i < n; i++) {
        ret.data[i] = va_arg(ap, size_t);
    }

    return ret;
}

bool is_element_of(int i, struct Set s)
{
    for(size_t n = 0; n < s.size; n++) {
        if(s.data[n] == i)
            return true;
    }

    return false;
}

bool is_empty(struct Set s)
{
    if(s.size)
        return true;
    else
        return false;
}

int iterate(struct Set s, int *iter)
{
    int ret = s.data[*iter];
    if(*iter == (int)(s.size))
        *iter = 0;
    else
        *iter += 1;
    return ret;
}

int *enumerate(struct Set s)
{
    int *ret = calloc(s.size, sizeof(int));
    ret = memcpy(ret, s.data, s.size);
    return ret;
}

struct Set intersec_set(struct Set s1, struct Set s2)
{
    size_t array_sz = 0;
    int *tmp = calloc(MAX(s1.size, s2.size), sizeof(int));

    for(size_t i = 0; i < s1.size; i++) {
        for(size_t n = 0; n < s2.size; n++) {
            if(s1.data[i] == s2.data[n]) {
                tmp[array_sz++] = s1.data[i];
            }
        }
    }

    struct Set ret = {
        .data = calloc(array_sz, sizeof(int)),
        .size = array_sz,
    };

    for(size_t i = 0; i < array_sz; i++)
        ret.data[i] = tmp[i];

    free(tmp);
    return ret;
}

bool is_subset(struct Set s1, struct Set s2)
{
    size_t j = 0;
    for(size_t i = 0; i < s1.size; i++) {
        for(size_t n = 0; n < s2.size; n++) {
            if(s1.data[i] == s2.data[n])
                j++;
        }
    }

    if(j == s1.size)
        return true;
    else
        return false;
}

struct Set union_set(struct Set s1, struct Set s2)
{
    size_t array_sz = 0;
    int *tmp = calloc(s1.size + s2.size, sizeof(int));

    size_t j = 0;
    for(size_t i = 0; i < s1.size; i++)
        tmp[array_sz++] = s1.data[i];

    printf("%d\n", array_sz);
    struct Set ret = {
        .data = calloc(array_sz, sizeof(int)),
        .size = array_sz,
    };

    for(size_t i = 0; i < array_sz; i++)
        ret.data[i] = tmp[i];
    free(tmp);

    return ret;
}

struct Set difference(struct Set s1, struct Set s2)
{
    size_t array_sz = 0;
    int *tmp = calloc(s1.size, sizeof(int));

    for(size_t i = 0; i < s1.size; i++) {
        for(size_t n = 0; n < s2.size; n++) {
            if(s1.data[i] != s2.data[n])
                tmp[array_sz++] = s1.data[i];
        }
    }

    struct Set ret = {
        .data = calloc(array_sz, sizeof(int)),
        .size = array_sz,
    };

    for(size_t i = 0; i < array_sz; i++)
        ret.data[i] = tmp[i];
    free(tmp);

    return ret;
}

size_t size(struct Set s)
{
    return s.size;
}

void free_set(struct Set *s)
{
    free(s->data);
    s->size = 0;
    s->data = NULL;
}

void print_set(struct Set s)
{
    for(size_t i = 0; i < s.size; i++) {
        printf("%d\n", s.data[i]);
    }
}

int main(void)
{
    struct Set set1 = create_set(5,
            1 << 1,
            1 << 2,
            1 << 3,
            1 << 4,
            1 << 5);
    struct Set set2 = create_set(4,
            1 << 6,
            1 << 3,
            1 << 4,
            1 << 1);
    struct Set intersec = intersec_set(set1, set2);
    print_set(intersec);
    struct Set u = union_set(set1, set2);
    print_set(u);

    free_set(&intersec);
    free_set(&set2);
    free_set(&set1);
    return EXIT_SUCCESS;
}
