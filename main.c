// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "main.h"

int main(void)
{
	char **args;
	int nr_args;
	hashtable_t *library = ht_create(HMAX, hash_function_string,
									 compare_function_strings);
	hashtable_t *ht_users = ht_create(HMAX, hash_function_string,
									  compare_function_strings);
	while (1) {
		char *command = malloc(LMAX * sizeof(char));
		DIE(!command, MALLOC_FAILED);
		fgets(command, LMAX, stdin);
		get_args(command, &args, &nr_args);

		if (!strcmp(args[0], "EXIT")) {
			exit_program(library, ht_users);
			free(command);
			free_args(args, nr_args);
			return 0;

		} else if (!strcmp(args[0], "ADD_BOOK")) {
			add_book(args, library, nr_args);

		} else if (!strcmp(args[0], "GET_BOOK")) {
			get_book(args, library, nr_args);

		} else if (!strcmp(args[0], "RMV_BOOK")) {
			rmv_book(args, library, nr_args);

		} else if (!strcmp(args[0], "ADD_DEF")) {
			add_def(args, library, nr_args);

		} else if (!strcmp(args[0], "GET_DEF")) {
			get_def(args, library, nr_args);

		} else if (!strcmp(args[0], "RMV_DEF")) {
			rmv_def(args, library, nr_args);

		} else if (!strcmp(args[0], "ADD_USER")) {
			add_user(args, ht_users);

		} else if (!strcmp(args[0], "BORROW")) {
			borrow(args, library, ht_users, nr_args);

		} else if (!strcmp(args[0], "RETURN")) {
			return_book(args, library, ht_users, nr_args);

		} else if (!strcmp(args[0], "LOST")) {
			lost(args, library, ht_users, nr_args);

		} else {
			printf("Invalid command!\n");
		}
		free(command);
		free_args(args, nr_args);
	}

	return 0;
}
