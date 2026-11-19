#ifndef CATALOG_H
#define CATALOG_H

#include "Movie.h"
#include <stddef.h>

typedef struct {
    Movie *movies;
    size_t size;
    size_t capacity;
} Catalog;

#endif