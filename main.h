// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef MAIN_H_
#define MAIN_H_

// Initial size for the array of buckets
#define HMAX 10

// Maximum size of an input line
#define LMAX 257

// Maximum number of arguments in a command
#define MAX_ARGS 15

// Maximum length of a pair of key and value
#define PMAX 45

// Maximum length of a bookname
#define BMAX 41

// Maximum length of a username, key or value
#define UKVMAX 21

typedef unsigned int uint_t;

// Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Headers
#include "hashtable.h"
#include "utilities.h"
#include "errors.h"
#include "commands.h"

// Structure that defines a book from a library
typedef struct book_t {
	int status;  // available (1), borrowed (0)
	double sum;
	double rating;
	int purchases;
	char book_name[BMAX];
	hashtable_t *content;
} book_t;

// Structure that defines a user from the system
typedef struct user_t {
	char user_name[UKVMAX];
	int score;
	int borrowed_books;
	char book_name[BMAX];
	int borrow_days;
} user_t;

#endif  // MAIN_H_
