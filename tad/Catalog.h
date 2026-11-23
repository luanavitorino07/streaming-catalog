#ifndef CATALOG_H
#define CATALOG_H

#include "Movie.h"
#include <stddef.h>

typedef struct {
    Movie *movies;
    size_t size;
    size_t capacity;
} Catalog;


typedef enum {
    OK,
    NOT_FOUND,
    MEMORY_ERROR
} CatalogStatus;



void catalogCreate(Catalog *catalog);
void catalogDestroy(Catalog *catalog);

CatalogStatus catalogInsert(Catalog *catalog, Movie movie);
CatalogStatus catalogUpdate(Catalog *catalog, int id, Movie movie_new);
CatalogStatus catalogRemove(Catalog *catalog, int id);

ptrdiff_t catalogSearchl(const Catalog *catalog, int id);



#endif