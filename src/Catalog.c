#include "../tad/Catalog.h"
#include <stdlib.h>

void catalogCreate(Catalog *catalog){
    catalog->movies = NULL;
    catalog->size = 0;
    catalog->capacity = 0;
    
}
void catalogDestroy(Catalog *catalog){
    free(catalog->movies);

    catalog->movies = NULL;
    catalog->size = 0;
    catalog->capacity = 0;
}

ptrdiff_t catalogSearchl(const Catalog *catalog, int id){
    for (size_t i = 0; i < catalog->size; i++) {
        if (catalog->movies[i].id == id) {
            return (ptrdiff_t)i;
        }
    }
    return -1;
}

static int catalogExpand(Catalog *catalog){
    size_t new_capacity;

    if (catalog->capacity == 0) {
        new_capacity = 10;
    } else {
        new_capacity = catalog->capacity  * 2;
    }

    Movie *movies_expand = realloc(
        catalog->movies,
        new_capacity * sizeof(Movie)
    );

    if (movies_expand == NULL) {
        return 0;
    }

    catalog->movies = movies_expand;
    catalog->capacity = new_capacity;

    return 1;
}

CatalogStatus catalogInsert(Catalog *catalog, Movie movie){
    if(catalog->size == catalog->capacity) {
        if(catalogExpand(catalog) == 0){
            return MEMORY_ERROR;
        }      
    }
    catalog->movies[catalog->size] = movie;
    catalog->size++;

    return OK;
}

CatalogStatus catalogUpdate(Catalog *catalog, int id, Movie movie_new){
    ptrdiff_t index = catalogSearchl(catalog, id);
    
    if(index == -1){
        return NOT_FOUND;
    }

    movie_new.id = id;
    catalog->movies[index] = movie_new;

    return OK;
}

CatalogStatus catalogRemove(Catalog *catalog, int id){
    ptrdiff_t index = catalogSearchl(catalog, id);
    
    if(index == -1){
        return NOT_FOUND;
    }

    for(size_t i = (size_t)index; i <catalog->size - 1; i++){
        catalog->movies[i] = catalog->movies[i+1];
    }

    return OK;
}



