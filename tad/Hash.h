#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include "Catalog.h"

typedef struct HashNode {
    int id;
    size_t pos;                 
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    size_t capacity;            
    size_t count;               
    unsigned long collisions;   
    unsigned long steps;        
} HashTable;

typedef enum {
    HASH_OK, HASH_NOT_FOUND, HASH_MEMORY_ERROR,
    HASH_DUPLICATED_ID, HASH_INVALID_ARGUMENT
} HashStatus;

HashStatus hash_create(HashTable *t, size_t capacity);
void       hash_destroy(HashTable *t);
HashStatus hash_insert(HashTable *t, int id, size_t pos);
HashStatus hash_remove(HashTable *t, int id);
ptrdiff_t  hash_search(HashTable *t, int id);   

size_t     hash_bucket(const HashTable *t, int id);
size_t     hash_capacity_for(size_t n, double alpha);
HashStatus hash_build(HashTable *t, const Catalog *c, double alpha);
double     hash_load_factor(const HashTable *t);
void       hash_reset_steps(HashTable *t);

#endif