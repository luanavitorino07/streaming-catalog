
#include "../tad/CSV.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_SIZE 8192
#define CSV_COLUMNS 18
#define MAX 150


static int parse_csv_line(char *line, char *fields[], int max_fields) {
    char *read = line;
    char *write = line;
    int count = 0;

    while (count < max_fields) {
        fields[count++] = write;

        if (*read == '"') {
            read++;

            while (*read) {
                if (*read == '"') {
                    if (read[1] == '"') {
                        *write++ = '"';
                        read += 2;
                    } else {
                        read++;
                        break;
                    }
                } else {
                    *write++ = *read++;
                }
            }

            while (*read && *read != ',') {
                if (*read != ' ' && *read != '\t') {
                    return -1;
                }
                read++;
            }
        } else {
            while (*read && *read != ',') {
                *write++ = *read++;
            }
        }

        int has_comma = (*read == ',');

        *write++ = '\0';

        if (!has_comma) {
            break;
        }

        read++;

        if (*read == '\0') {
            if (count < max_fields) {
                fields[count++] = write;
                *write = '\0';
            }
            break;
        }
    }

    return count;
}


static int parse_int(const char *text) {
    char *end;
    long value;

    if (text == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    value = strtol(text, &end, 10);

    if (errno != 0 || *end != '\0') {
        return 0;
    }

    return (int)value;
}

static float parse_float(const char *text) {
    char *end;
    float value;

    if (text == NULL || *text == '\0') {
        return 0.0f;
    }

    errno = 0;
    value = strtof(text, &end);

    if (errno != 0 || *end != '\0') {
        return 0.0f;
    }

    return value;
}

static void copy_field(char *destination, size_t size, const char *source) {
    if (size == 0) {
        return;
    }

    snprintf(destination, size, "%s", source);
}

int import_csv(Catalog *catalog, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    char line[MAX_LINE_SIZE];

    /* Skip the CSV header. */
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *fields[CSV_COLUMNS];

        line[strcspn(line, "\r\n")] = '\0';

        int count = parse_csv_line(line, fields, CSV_COLUMNS);

        if (count != CSV_COLUMNS) {
            fprintf(stderr,
                "CSV error: invalid number of columns. Expected %d, got %d.\n",
                CSV_COLUMNS, count);

            fclose(file);
            return 0;
        }
        
        Movie movie = {0};

        movie.id = (int)catalog->size + 1;

        copy_field(movie.title, MAX, fields[0]);
        movie.year = parse_int(fields[1]);
        copy_field(movie.certificate, MAX, fields[2]);
        movie.runtime = parse_int(fields[3]);
        copy_field(movie.genre,MAX, fields[4]);
        movie.rating = parse_float(fields[5]);
        copy_field(movie.director,MAX, fields[8]);
        movie.votes = parse_int(fields[13]);

        if (catalogInsert(catalog, movie) != OK) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
