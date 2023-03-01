// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "main.h"

// Structure that defines an element of a list
typedef struct node_t {
	void* data;
	struct node_t* next;
} node_t;

// Structure that defines a linear singly linked list
typedef struct list_t {
	node_t* head;
	uint_t data_size;
	uint_t size;
} list_t;

// Structure that defines the data of a node in a hashtable
typedef struct info_t {
	void *key;
	void *value;
} info_t;

// Structure that defines a hastable
typedef struct hashtable_t {
	list_t **buckets;
	uint_t size;
	uint_t hmax;
	uint_t (*hash_function)(void*);
	int (*compare_function)(void*, void*);
} hashtable_t;

// Function that creates a singly linked list
extern list_t *ll_create(uint_t data_size);

// Function that adds a node to the n-th position of a list
extern void ll_add_nth_node(list_t* list, uint_t n, const void* new_data);

// Function that removes a node from the n-th position in a list
extern node_t *ll_remove_nth_node(list_t* list, uint_t n);

// Function that deallocates the memory used by a list
extern void ll_free(list_t** pp_list);

// Function that creates a hash for a string
// Credits: http://www.cse.yorku.ca/~oz/hash.html
extern uint_t hash_function_string(void *a);

// Function that creates a hashtable
extern hashtable_t * ht_create(uint_t hmax, uint_t (*hash_function)(void*),
							   int (*compare_function)(void*, void*));

// Function that checks if a hashtable has a specified key
extern int ht_has_key(hashtable_t *ht, void *key);

// Function that gets the value stored at a specified key
extern void * ht_get(hashtable_t *ht, void *key);

// Function that puts a new entry associated with a specified key
extern void ht_put(hashtable_t *ht, void *key, uint_t key_size, void *value,
				   uint_t value_size);

// Function that removes the entry associated with a specified key
extern void ht_remove_entry(hashtable_t *ht, void *key, int type);

// Function that resizes a hashtable that has a load factor above 1
extern void ht_resize(hashtable_t *ht);

// Function that frees the memory occupied by a hashtable
extern void ht_free(hashtable_t *ht);

#endif  // HASHTABLE_H_
