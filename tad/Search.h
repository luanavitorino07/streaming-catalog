
#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>
#include "Movie.h"


ptrdiff_t linear_search(const Movie arr[], size_t n, int id);
ptrdiff_t binary_search(const Movie arr[], size_t n, int id);
ptrdiff_t interpolation_search(const Movie arr[], size_t n, int id);


ptrdiff_t linear_search_title(const Movie arr[],size_t n,const char *title);
ptrdiff_t binary_search_title(const Movie arr[],size_t n,const char *title);

#endif
