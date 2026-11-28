#ifndef SORT_H
#define SORT_H

#include <stddef.h>
#include "Movie.h"

typedef enum {
    SORT_BY_RATING,
    SORT_BY_YEAR,
    SORT_BY_VOTES, 
    SORT_BY_TITLE,
    SORT_BY_ID
} SortCriteria;

void insertion_sort(Movie arr[], size_t n, SortCriteria criteria);

void quick_sort_first_pivot(Movie arr[], size_t n, SortCriteria criteria);

void quick_sort_random_pivot(Movie arr[], size_t n, SortCriteria criteria);


void   heap_build(Movie arr[], size_t n, SortCriteria criteria);
size_t heap_extract_max(Movie arr[], size_t active, SortCriteria criteria);
void   heap_sort(Movie arr[], size_t n, SortCriteria criteria);

#endif
