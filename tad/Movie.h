#ifndef MOVIE_H
#define MOVIE_H

#define MAX_STR 150

typedef struct {
    int id;

    char title[MAX_STR];
    char genre[MAX_STR];
    char certificate[MAX_STR];
    char director[MAX_STR];

    int year;
    int runtime;
    int votes;
    float rating;
} Movie;


#endif