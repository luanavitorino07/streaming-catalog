#include <stdio.h>
#include "../tad/Catalog.h"
#include "../tad/CSV.h"

int main(void) {
    Catalog catalog;

    catalogCreate(&catalog);

    if (!import_csv(&catalog, "data/imdb_clean.csv")) {
        printf("Error importing CSV.\n");
        catalogDestroy(&catalog);
        return 1;
    }

    printf("Movies imported: %zu\n", catalog.size);

    for (size_t i = 0; i < 5 && i < catalog.size; i++) {
        printf(
            "%d | %s | %d | %.1f\n",
            catalog.movies[i].id,
            catalog.movies[i].title,
            catalog.movies[i].year,
            catalog.movies[i].rating
        );
    }

    catalogDestroy(&catalog);

    return 0;
}