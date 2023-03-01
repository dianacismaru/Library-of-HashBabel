// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef ERRORS_H_
#define ERRORS_H_

#include <errno.h>

// Macro that is useful for handling error codes
#define DIE(assertion, call_description)                                      \
	do {                                                                      \
		if (assertion) {                                                      \
			fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                \
			perror(call_description);                                         \
			exit(errno);                                                      \
		}                                                                     \
	} while (0)

// Displayed message when failing dynamic memory allocation
#define MALLOC_FAILED "Malloc failed.\n"

// This type of error occurs when the specified book is not in the library
#define BOOK_NOT_IN_LIBRARY	"The book is not in the library.\n"

// This error occurs if the definition coresponding the specified key is not
// in the library
#define DEF_NOT_IN_BOOK "The definition is not in the book.\n"

// This error occurs when the specified user is already registered into the
// system
#define USER_ALREADY_REGISTERED "User is already registered.\n"

// This error occurs ........... TODO
// userul nu exista in sistem
#define USER_NOT_REGISTERED "You are not registered yet.\n"

// This error occurs if a user tries to borrow a book that is already borrowed
#define BORROWED_BOOK "The book is borrowed.\n"

// This error occurs if a user tries to borrow a book, but has already borrowed
// a book that has not been returned yet
#define ALREADY_BORROWED_A_BOOK "You have already borrowed a book.\n"

// This message is displayed when a user has reached a negative score
#define USER_BANNED "The user %s has been banned from this library.\n"

// This error occurs when a user that has been banned from the system tries to
// do something at the library
#define ALREADY_BANNED "You are banned from this library.\n"

// This error occurs when a user is trying to return a book that he hasn't ever
// borrowed
#define OTHER_BOOK "You didn't borrow this book.\n"

#endif  // ERRORS_H_
