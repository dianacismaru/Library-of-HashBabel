// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "main.h"

// Function that frees the memory occupied by an array of words
extern void free_args(char **args, int nr_args);

// Function that extracts the arguments from a command and places them into
// an array of words
extern void get_args(char *command, char ***args, int *nr_args);

// Function that compares two strings
// Credits: https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04
extern int compare_function_strings(void *a, void *b);

// Function that compares two books
extern int compare_function_books(const void *a, const void *b);

// Function that compares two users
extern int compare_function_users(const void *a, const void *b);

// Function that displays the book ranking
extern void top_books(hashtable_t *library);

// Function that displays the user ranking
extern void top_users(hashtable_t *ht_users);

#endif  // UTILITIES_H_
