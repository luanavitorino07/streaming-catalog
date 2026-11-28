#include <stdint.h>
#include <stdlib.h>
#include "../tad/Hash.h"

size_t hash_bucket(const HashTable *t, int id) {
    uint32_t h = (uint32_t)id * 2654435761u;
    return (size_t)(h % t->capacity);
}

HashStatus hash_create(HashTable *t, size_t capacity) {
    if (capacity == 0) return HASH_INVALID_ARGUMENT;

    t->buckets = calloc(capacity, sizeof(HashNode *));
    t->capacity = 0; 
    t->count = 0; 
    t->collisions = 0; 
    t->steps = 0;

    if (t->buckets == NULL) return HASH_MEMORY_ERROR;
    t->capacity = capacity;

    return HASH_OK;
}

void hash_destroy(HashTable *t) {
    if (t->buckets != NULL) {
        for (size_t b = 0; b < t->capacity; b++) {
            HashNode *n = t->buckets[b];
            while (n != NULL) {
                HashNode *next = n->next;
                free(n);
                n = next;
            }
        }
        free(t->buckets);
    }

    t->buckets = NULL; 
    t->capacity = 0; 
    t->count = 0;
    t->collisions = 0; 
    t->steps = 0;
}

HashStatus hash_insert(HashTable *t, int id, size_t pos) {
    if (t->buckets == NULL || id < 0) return HASH_INVALID_ARGUMENT;

    size_t b = hash_bucket(t, id);

    for (HashNode *n = t->buckets[b]; n != NULL; n = n->next){
        if (n->id == id) return HASH_DUPLICATED_ID;
    }

    HashNode *node = malloc(sizeof *node);

    if (node == NULL) return HASH_MEMORY_ERROR;
    if (t->buckets[b] != NULL) t->collisions++;   

    node->id = id; node->pos = pos;
    node->next = t->buckets[b];

    t->buckets[b] = node;
    t->count++;

    return HASH_OK;
}

HashStatus hash_remove(HashTable *t, int id) {
    if (t->buckets == NULL || id < 0) return HASH_INVALID_ARGUMENT;

    HashNode **pp = &t->buckets[hash_bucket(t, id)];

    while (*pp != NULL) {
        if ((*pp)->id == id) {
            HashNode *dead = *pp;
            *pp = dead->next;          
            free(dead);
            t->count--;
            return HASH_OK;
        }
        pp = &(*pp)->next;
    }
    return HASH_NOT_FOUND;
}

ptrdiff_t hash_search(HashTable *t, int id) {
    if (t->buckets == NULL || id < 0) return -1;

    for (HashNode *n = t->buckets[hash_bucket(t, id)]; n; n = n->next) {
        t->steps++;
        if (n->id == id) return (ptrdiff_t)n->pos;
    }

    return -1;
}

size_t hash_capacity_for(size_t n, double alpha) {
    if (n == 0 || alpha <= 0.0) return 1;

    size_t m = (size_t)((double)n / alpha);
    if ((double)m * alpha < (double)n) m++;    

    return m ? m : 1;
}

HashStatus hash_build(HashTable *t, const Catalog *c, double alpha) {
    if (alpha <= 0.0) return HASH_INVALID_ARGUMENT;

    hash_destroy(t);

    HashStatus s = hash_create(t, hash_capacity_for(c->size, alpha));
    if (s != HASH_OK) return s;

    for (size_t i = 0; i < c->size; i++) {
        s = hash_insert(t, c->movies[i].id, i);
        if (s != HASH_OK) { 
            hash_destroy(t); 
            return s; 
        }
    }
    return HASH_OK;
}

double hash_load_factor(const HashTable *t) {
    return t->capacity ? (double)t->count / (double)t->capacity : 0.0;
}

void hash_reset_steps(HashTable *t) { t->steps = 0; }