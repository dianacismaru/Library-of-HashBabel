// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "main.h"

// Function that frees the memory occupied by an array of words
void free_args(char **args, int nr_args)
{
	for (int i = 0; i < nr_args; i++)
		free(args[i]);
	free(args);
}

// Function that extracts the arguments from a command and places them into
// an array of words
void get_args(char *command, char ***args, int *nr_args)
{
	// Alloc memory for the number of arguments
	*args = malloc(MAX_ARGS * sizeof(char *));
	DIE(!(*args), MALLOC_FAILED);

	// Get the first argument
	char *p = strtok(command, " \n\"");

	*nr_args = 0;
	while (p) {
		// Alloc memory for each argument of the command
		(*args)[*nr_args] = malloc(strlen(p) + 1);
		DIE(!(*args)[*nr_args], MALLOC_FAILED);

		strcpy((*args)[*nr_args], p);
		(*nr_args)++;
		p = strtok(NULL, " \n\"");
	}
}

// Function that  compares two strings
// Credits: https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04
int compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

// Function that  compares two books
int compare_function_books(const void *a, const void *b)
{
	book_t *aux_a = (book_t *)a;
	book_t *aux_b = (book_t *)b;

	if (aux_a->rating > aux_b->rating)
		return -1;
	else if (aux_a->rating < aux_b->rating)
		return 1;
	else if (aux_a->purchases > aux_b->purchases)
		return -1;
	else if (aux_a->purchases < aux_b->purchases)
		return 1;
	else
		return strcmp(aux_a->book_name, aux_b->book_name);
}

// Function that  compares two users
int compare_function_users(const void *a, const void *b)
{
	user_t *aux_a = (user_t *)a;
	user_t *aux_b = (user_t *)b;

	if (aux_a->score > aux_b->score)
		return -1;
	else if (aux_a->score < aux_b->score)
		return 1;
	else
		return strcmp(aux_a->user_name, aux_b->user_name);
}

// Function that displays the book ranking
void top_books(hashtable_t *library)
{
	book_t *v = malloc(library->size * sizeof(book_t));
	DIE(!v, MALLOC_FAILED);

	// Create an array of books
	int ct = 0;
	for (uint_t i = 0; i < library->hmax; i++) {
		if (library->buckets[i]->head) {
			node_t *aux = library->buckets[i]->head;
			while (aux) {
				// Place the book into the array
				book_t *details = (*(info_t*)aux->data).value;
				v[ct++] =  *details;
				aux = aux->next;
			}
		}
	}
	// Sort the array
	qsort(v, ct, sizeof(book_t), compare_function_books);

	printf("Books ranking:\n");
	for (int i = 0; i < ct; i++)
		printf("%d. Name:%s Rating:%0.3f Purchases:%d\n", i + 1,
			   v[i].book_name, v[i].rating, v[i].purchases);

	free(v);
}

// Function that displays the user ranking
void top_users(hashtable_t *ht_users)
{
	user_t *v = malloc(ht_users->size * sizeof(user_t));
	DIE(!v, MALLOC_FAILED);

	// Create an array of users
	int ct = 0;
	for (uint_t i = 0; i < ht_users->hmax; i++) {
		if (ht_users->buckets[i]->head) {
			node_t *aux = ht_users->buckets[i]->head;
			while (aux) {
				// Place the book into the array
				user_t *user = (*(info_t*)aux->data).value;
				if (user->score >= 0)
					v[ct++] =  *user;
				aux = aux->next;
			}
		}
	}
	// Sort the array
	qsort(v, ct, sizeof(user_t), compare_function_users);

	printf("Users ranking:\n");
	for (int i = 0; i < ct; i++)
		printf("%d. Name:%s Points:%d\n", i + 1, v[i].user_name, v[i].score);

	free(v);
}
