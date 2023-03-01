// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "main.h"

// Function that frees all the allocated memory and displays the rankings
void exit_program(hashtable_t *library, hashtable_t *ht_users)
{
	top_books(library);
	top_users(ht_users);

	for (uint_t i = 0; i < library->hmax; i++) {
		if (library->buckets[i]->head) {
			node_t *aux = library->buckets[i]->head;
			while (aux) {
				free((*(info_t*)aux->data).key);
				book_t *details = (*(info_t*)aux->data).value;
				ht_free(details->content);
				free(details);
				aux = aux->next;
			}
		}
		ll_free(&library->buckets[i]);
	}
	free(library->buckets);
	free(library);

	ht_free(ht_users);
}

// Function that adds a new book into the library
void add_book(char **args, hashtable_t *library, int nr_args)
{
	// Initialize the book
	book_t details;
	details.status = 1;
	details.sum = 0;
	details.rating = 0;
	details.purchases = 0;

	// Get the entire book name
	strcpy(details.book_name, args[1]);
	for (int i = 2; i < nr_args - 1; i++) {
		strcat(details.book_name, " ");
		strcat(details.book_name, args[i]);
	}

	// Check if the key already exists
	if (ht_has_key(library, details.book_name))
		ht_remove_entry(library, details.book_name, 0);

	hashtable_t *new_book = ht_create(10, hash_function_string,
									  compare_function_strings);

	int def_number = atoi(args[nr_args - 1]);
	for (int i = 0; i < def_number; i++) {
		char *command = malloc(PMAX * sizeof(char));
		DIE(!command, MALLOC_FAILED);
		fgets(command, PMAX, stdin);

		// Extract def_key and def_val arguments
		int nr_args;
		char **pair;
		get_args(command, &pair, &nr_args);
		char def_key[UKVMAX], def_val[UKVMAX];
		strcpy(def_key, pair[0]);
		strcpy(def_val, pair[1]);

		// If the definition already exists in the book
		if (ht_has_key(new_book, def_key))
			ht_remove_entry(new_book, def_key, 1);

		// Place key and value into the new book
		ht_put(new_book, def_key, sizeof(def_key), def_val,
			   sizeof(def_val));

		free(command);
		free_args(pair, nr_args);
	}
	// Place the book into the library
	details.content = new_book;

	ht_put(library, details.book_name, sizeof(details.book_name),
		   &details, sizeof(details));
}

// Function that prints a book's details
void get_book(char **args, hashtable_t *library, int nr_args)
{
	// Get the entire book name
	char book_name[BMAX];
	strcpy(book_name, args[1]);
	for (int i = 2; i < nr_args; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	if (!ht_has_key(library, book_name)) {
		printf(BOOK_NOT_IN_LIBRARY);
		return;
	}

	book_t *details = ht_get(library, book_name);
	printf("Name:%s Rating:%0.3f Purchases:%d\n", details->book_name,
		   details->rating, details->purchases);
}

// Function that removes a book from the library
void rmv_book(char **args, hashtable_t *library, int nr_args)
{
	// Get the entire book name
	char book_name[BMAX];
	strcpy(book_name, args[1]);
	for (int i = 2; i < nr_args; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	if (!ht_has_key(library, book_name)) {
		printf(BOOK_NOT_IN_LIBRARY);
		return;
	}

	// Remove the book from the library
	ht_remove_entry(library, book_name, 0);
}

// Function that adds a new definition into a specified book
void add_def(char **args, hashtable_t *library, int nr_args)
{
	// Get the entire book name
	char book_name[BMAX];
	int i;
	strcpy(book_name, args[1]);
	for (i = 2; i < nr_args - 2; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	if (!ht_has_key(library, book_name)) {
		printf(BOOK_NOT_IN_LIBRARY);
		return;
	}

	book_t *details = ht_get(library, book_name);

	char def_key[UKVMAX], def_val[UKVMAX];
	strcpy(def_key, args[i]);
	strcpy(def_val, args[i + 1]);

	// If the definition already exists in the book
	if (ht_has_key(details->content, def_key))
		ht_remove_entry(details->content, def_key, 1);

	// Place key and value into the book
	ht_put(details->content, def_key, sizeof(def_key), def_val,
		   sizeof(def_val));
}

// Function that gets a definition from a specified book
void get_def(char **args, hashtable_t *library, int nr_args)
{
	// Get the entire book name
	char book_name[BMAX];
	strcpy(book_name, args[1]);
	for (int i = 2; i < nr_args - 1; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	if (!ht_has_key(library, book_name)) {
		printf(BOOK_NOT_IN_LIBRARY);
		return;
	}
	book_t *details = ht_get(library, book_name);

	char def_key[UKVMAX];
	strcpy(def_key, args[nr_args - 1]);

	if (!ht_has_key(details->content, def_key)) {
		printf(DEF_NOT_IN_BOOK);
		return;
	}
	char *def_val = ht_get(details->content, def_key);
	printf("%s\n", def_val);
}

// Function that removes a definition from a specified book
void rmv_def(char **args, hashtable_t *library, int nr_args)
{
	// Get the entire book name
	char book_name[BMAX];
	strcpy(book_name, args[1]);
	int i;
	for (i = 2; i < nr_args - 1; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	if (!ht_has_key(library, book_name)) {
		printf(BOOK_NOT_IN_LIBRARY);
		return;
	}

	book_t *details = ht_get(library, book_name);

	char def_key[UKVMAX];
	strcpy(def_key, args[i]);
	if (!ht_has_key(details->content, def_key)) {
		printf(DEF_NOT_IN_BOOK);
		return;
	}

	ht_remove_entry(details->content, def_key, 1);
}

// Function that adds a user into the library system
void add_user(char **args, hashtable_t *ht_users)
{
	char user_name[UKVMAX];
	strcpy(user_name, args[1]);

	if (ht_has_key(ht_users, user_name)) {
		printf(USER_ALREADY_REGISTERED);
		return;
	}

	// Initialize the user
	user_t new_user;
	new_user.score = 100;
	new_user.borrowed_books = 0;
	strcpy(new_user.user_name, user_name);

	ht_put(ht_users, user_name, sizeof(user_name), &new_user,
		   sizeof(new_user));
}

// Function that is called when a user tries to borrow a book
void borrow(char **args, hashtable_t *library, hashtable_t *ht_users,
			int nr_args)
{
	char user_name[UKVMAX];
	strcpy(user_name, args[1]);

	// Check if the user is registered into the system
	if (!ht_has_key(ht_users, user_name)) {
		printf(USER_NOT_REGISTERED);
		return;
	}

	user_t *user = ht_get(ht_users, user_name);

	// Check if the user is banned
	if (user->score < 0) {
		printf(ALREADY_BANNED);
		return;
	}

	// Check if the user already has already borrowed a book that has not been
	// returned yet
	if (user->borrowed_books) {
		printf(ALREADY_BORROWED_A_BOOK);
		return;
	}

	// Get the entire book name
	char book_name[BMAX];
	strcpy(book_name, args[2]);
	for (int i = 3; i < nr_args - 1; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	// Check if the wanted book exists
	if (!ht_has_key(library, book_name)) {
		printf(BOOK_NOT_IN_LIBRARY);
		return;
	}
	book_t *details = ht_get(library, book_name);

	// Check if the wanted book is available
	if (!details->status) {
		printf(BORROWED_BOOK);
		return;
	}
	user->borrow_days = atoi(args[nr_args - 1]);
	strcpy(user->book_name, book_name);
	user->borrowed_books = 1;
	details->status = 0;
}

// Function that is called when a user tries to return a book
void return_book(char **args, hashtable_t *library, hashtable_t *ht_users,
				 int nr_args)
{
	char user_name[UKVMAX];
	strcpy(user_name, args[1]);

	// Check if the user is registered into the system
	if (!ht_has_key(ht_users, user_name)) {
		printf(USER_NOT_REGISTERED);
		return;
	}

	user_t *user = ht_get(ht_users, user_name);

	// Check if the user is banned
	if (user->score < 0) {
		printf(ALREADY_BANNED);
		return;
	}

	// Get the entire book name
	char book_name[BMAX];
	strcpy(book_name, args[2]);
	for (int i = 3; i < nr_args - 2; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	// Check if the user is trying to return a book that he actually borrowed
	if (!(user->borrowed_books) || strcmp(user->book_name, book_name)) {
		printf(OTHER_BOOK);
		return;
	}

	int days_since_borrow = atoi(args[nr_args - 2]);
	int rating = atoi(args[nr_args - 1]);
	user->borrowed_books = 0;

	// Calculate the number of days left until the borrow deadline
	int days = user->borrow_days - days_since_borrow;
	if (days < 0)
		user->score += days * 2;
	else
		user->score += days;

	book_t *details = ht_get(library, book_name);
	details->status = 1;
	details->sum += rating;
	details->purchases++;
	details->rating = details->sum / details->purchases;

	if (user->score < 0)
		printf(USER_BANNED, user_name);
}

// Function that is called when a user has lost a book
void lost(char **args, hashtable_t *library, hashtable_t *ht_users,
		  int nr_args)
{
	char user_name[UKVMAX];
	strcpy(user_name, args[1]);

	// Check if the user is registered into the system
	if (!ht_has_key(ht_users, user_name)) {
		printf(USER_NOT_REGISTERED);
		return;
	}

	user_t *user = ht_get(ht_users, user_name);
	// Check if the user is banned
	if (user->score < 0) {
		printf(ALREADY_BANNED);
		return;
	}

	user->score -= 50;
	user->borrowed_books = 0;

	// Get the entire book name
	char book_name[BMAX];
	strcpy(book_name, args[2]);
	for (int i = 3; i < nr_args; i++) {
		strcat(book_name, " ");
		strcat(book_name, args[i]);
	}

	// Remove the book from the library
	ht_remove_entry(library, book_name, 0);

	if (user->score < 0)
		printf(USER_BANNED, user_name);
}
