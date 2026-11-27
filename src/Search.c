#include <string.h>
#include "../tad/Search.h"

ptrdiff_t linear_search(const Movie arr[], size_t n, int id) {
    for (size_t i = 0; i < n; i++) {

        if (arr[i].id == id) {
            return (ptrdiff_t)i;
        }
    }

    return -1;
}

ptrdiff_t binary_search(const Movie arr[], size_t n, int id) {
    size_t left = 0;
    size_t right = n;

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid].id == id) {
            return (ptrdiff_t)mid;
        }

        if (arr[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return -1;
}

ptrdiff_t interpolation_search(const Movie arr[],size_t n,int id) {
    if (n == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low <= high &&
           id >= arr[low].id &&
           id <= arr[high].id) {

        if (arr[low].id == arr[high].id) {

            if (arr[low].id == id) {
                return (ptrdiff_t)low;
            }

            return -1;
        }

        long double fraction =
            (long double)(id - arr[low].id) /
            (arr[high].id - arr[low].id);

        size_t pos = low +
            (size_t)(fraction * (high - low));

        if (arr[pos].id == id) {
            return (ptrdiff_t)pos;
        }

        if (arr[pos].id < id) {
            low = pos + 1;
        } else {

            if (pos == 0) {
                return -1;
            }

            high = pos - 1;
        }
    }

    return -1;
}




ptrdiff_t linear_search_title(const Movie arr[],size_t n,const char *title) {
    for (size_t i = 0; i < n; i++) {
        if (strcmp(arr[i].title, title) == 0) {
            return (ptrdiff_t)i;
        }
    }

    return -1;
}

ptrdiff_t binary_search_title(const Movie arr[],size_t n,const char *title) {
    size_t left = 0;
    size_t right = n;

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        int comparison = strcmp(arr[mid].title, title);

        if (comparison == 0) {
            return (ptrdiff_t)mid;
        }

        if (comparison < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return -1;
}
