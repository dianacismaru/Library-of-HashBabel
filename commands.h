// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "main.h"

// Function that frees all the allocated memory and displays the rankings
extern void exit_program(hashtable_t *library, hashtable_t *ht_users);

// Function that adds a new book into the library
extern void add_book(char **args, hashtable_t *library, int nr_args);

// Function that prints a book's details
extern void get_book(char **args, hashtable_t *library, int nr_args);

// Function that removes a book from the library
extern void rmv_book(char **args, hashtable_t *library, int nr_args);

// Function that adds a new definition into a specified book
extern void add_def(char **args, hashtable_t *library, int nr_args);

// Function that gets a definition from a specified book
extern void get_def(char **args, hashtable_t *library, int nr_args);

// Function that removes a definition from a specified book
extern void rmv_def(char **args, hashtable_t *library, int nr_args);

// Function that adds a user into the library system
extern void add_user(char **args, hashtable_t *ht_users);

// Function that is called when a user tries to borrow a book
extern void borrow(char **args, hashtable_t *library, hashtable_t *ht_users,
				 int nr_args);

// Function that is called when a user tries to return a book
extern void return_book(char **args, hashtable_t *library,
						hashtable_t *ht_users, int nr_args);

// Function that is called when a user has lost a book
extern void lost(char **args, hashtable_t *library, hashtable_t *ht_users,
				 int nr_args);

#endif  // COMMANDS_H_
