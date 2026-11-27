#ifndef SORT_H
#define SORT_H

#include <stddef.h>
#include "../tad/Movie.h"

typedef enum {
    SORT_BY_RATING,
    SORT_BY_YEAR,
    SORT_BY_VOTES
} SortCriteria;

void insertion_sort(Movie arr[], size_t n, SortCriteria criteria);

void quick_sort_first_pivot(Movie arr[], size_t n, SortCriteria criteria);

void quick_sort_random_pivot(Movie arr[], size_t n, SortCriteria criteria);

#endif
