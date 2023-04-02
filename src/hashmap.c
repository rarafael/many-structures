#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Hashmap {
    int *hash;
    int *data;
    size_t size;
};

struct Hashmap new_hashmap(const char *str, int data);
void new_entry(const char *str, int data, struct Hashmap *hm);
int get_data(const char *str, struct Hashmap hm);
void remove_entry(const char *str, struct Hashmap *hm);
void print_entries(struct Hashmap hm);
void destroy_hashmap(struct Hashmap hm);

static inline int get_hash(const char *string)
{
    int ret = 0;
    for(size_t i = 0; i < strlen(string); i++) {
        ret += (i % 10) * (int)string[i];
    }

    return ret;
}

struct Hashmap new_hashmap(const char *str, int data)
{
    struct Hashmap ret = {
        .hash = NULL,
        .data = NULL,
        .size = 1,
    };

    ret.hash = malloc(ret.size * sizeof(int));
    ret.data = malloc(ret.size * sizeof(int));

    ret.hash[0] = get_hash(str);
    ret.data[0] = data;

    return ret;
}

void new_entry(const char *str, int data, struct Hashmap *hm)
{
    hm->size += 1;

    hm->hash = realloc(hm->hash, hm->size * sizeof(int));
    hm->data = realloc(hm->data, hm->size * sizeof(int));

    hm->hash[hm->size - 1] = get_hash(str);
    hm->data[hm->size - 1] = data;
}

void remove_entry(const char *str, struct Hashmap *hm)
{
    int hash = get_hash(str);
    size_t i;
    for(i = 0; i < hm->size + 1; i++) {
        if(i == hm->size)
            return;
        if(hm->hash[i] == hash)
            break;
    }

    hm->hash[i] = 0;
    hm->data[i] = 0;

    struct Hashmap tmp = {
        .hash = realloc(hm->hash, (hm->size - 1) * sizeof(int)),
        .data = realloc(hm->data, (hm->size - 1) * sizeof(int)),
        .size = hm->size - 1,
    };

    size_t j = 0;
    for(size_t n = 0; n < hm->size; n++) {
        if(hm->hash[n] != 0 && hm->data[n] != 0) {
            tmp.hash[j] = hm->hash[n];
            tmp.data[j] = hm->data[n];
            j += 1;
        }
    }

    hm->hash = tmp.hash;
    hm->data = tmp.data;
    hm->size = tmp.size;
}

int get_data(const char *str, struct Hashmap hm)
{
    int hash = get_hash(str);
    for(size_t i = 0; i < hm.size; i++) {
        if(hm.hash[i] == hash)
            return hm.data[i];
    }

    return INT_MAX;
}

void print_entries(struct Hashmap hm)
{
    for(size_t i = 0; i < hm.size; i++) {
        printf("%6d: %d\n", hm.hash[i], hm.data[i]);
    }
}

void destroy_hashmap(struct Hashmap hm)
{
    free(hm.hash);
    free(hm.data);
}

int main(void)
{
    struct Hashmap hm = new_hashmap("rafael", 1 << 1);
    new_entry("rarafael", 1 << 2, &hm);
    print_entries(hm);
    destroy_hashmap(hm);
    return EXIT_SUCCESS;
}
