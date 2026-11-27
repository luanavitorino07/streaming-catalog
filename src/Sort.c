
#include <stdlib.h>

#include "../tad/Sort.h"


static int compare_movies(const Movie *a, const Movie *b, SortCriteria criteria) {
    switch (criteria) {
        case SORT_BY_RATING:
            if (a->rating < b->rating) return -1;
            if (a->rating > b->rating) return 1;
            break;

        case SORT_BY_YEAR:
            if (a->year < b->year) return -1;
            if (a->year > b->year) return 1;
            break;

        case SORT_BY_VOTES:
            if (a->votes < b->votes) return -1;
            if (a->votes > b->votes) return 1;
            break;
    }

    // remove ambiguidades comparando por ids 
    if (a->id < b->id) return -1;
    if (a->id > b->id) return 1;

    return 0;
}




void insertion_sort(Movie arr[], size_t n, SortCriteria criteria) {
    if (n < 2) {
        return;
    }
    for (size_t i = 1; i < n; i++) {
        Movie key = arr[i];
        size_t j = i;

        while (j > 0 && compare_movies(&arr[j - 1], &key, criteria) > 0) {
            arr[j] = arr[j - 1];
            j--;
        }

        arr[j] = key;
    }
}

static size_t partition(Movie arr[], size_t left, size_t right, SortCriteria criteria) {
    Movie pivot = arr[right - 1];
    size_t i = left;

    for (size_t j = left; j < right - 1; j++) {
        if (compare_movies(&arr[j], &pivot, criteria) <= 0) {
            Movie temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
        }
    }

    Movie temp = arr[i];
    arr[i] = arr[right - 1];
    arr[right - 1] = temp;

    return i;
}

static void quick_sort_recursive(Movie arr[], size_t left, size_t right, SortCriteria criteria, int random_pivot) {
    if (right - left <= 1) {
        return;
    }

    size_t pivot_index;

    if (random_pivot) {
        pivot_index = left + (size_t)rand() % (right - left);
    } else {
        pivot_index = left;
    }

    Movie temp = arr[pivot_index];
    arr[pivot_index] = arr[right - 1];
    arr[right - 1] = temp;

    size_t p = partition(arr, left, right, criteria);

    quick_sort_recursive(arr, left, p, criteria, random_pivot);

    quick_sort_recursive(arr, p + 1, right, criteria, random_pivot);
}

void quick_sort_first_pivot(Movie arr[], size_t n, SortCriteria criteria) {
    quick_sort_recursive(arr, 0, n, criteria, 0);
}

void quick_sort_random_pivot(Movie arr[], size_t n, SortCriteria criteria) {
    quick_sort_recursive(arr, 0, n, criteria, 1);
}
