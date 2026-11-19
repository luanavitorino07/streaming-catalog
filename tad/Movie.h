#ifndef MOVIE_H
#define MOVIE_H

#define MAX 150

typedef struct {
    int id;

    char title[MAX];
    char genre[MAX];
    char certificate[MAX];
    char director[MAX];

    int year;
    int runtime;
    int votes;

    float rating;
} Movie;


#endif