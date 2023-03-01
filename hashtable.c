
// Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

#include "main.h"

// Function that  creates a linked list
// Credits: https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04
list_t *ll_create(uint_t data_size)
{
	list_t* ll = malloc(sizeof(list_t));
	DIE(!ll, MALLOC_FAILED);
	ll->head = NULL;
	ll->data_size = data_size;
	ll->size = 0;
	return ll;
}

// Function that  adds a node to the n-th position of a list
// Credits: https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04
void ll_add_nth_node(list_t *list, uint_t n, const void *new_data)
{
	if (!list)
		return;

	if (n > list->size)
		n = list->size;

	node_t *prev = NULL, *curr = list->head;
	while (n > 0) {
		prev = curr;
		curr = curr->next;
		n--;
	}

	// Create a new node
	node_t* new_node = malloc(sizeof(node_t));
	DIE(!new_node, MALLOC_FAILED);
	new_node->data = malloc(list->data_size);
	DIE(!new_node->data, MALLOC_FAILED);
	memcpy(new_node->data, new_data, list->data_size);
	new_node->next = curr;

	if (prev == NULL)
		list->head = new_node;
	else
		prev->next = new_node;

	list->size++;
}

// Function that  removes a node from the n-th position in a list
// Credits: https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04
node_t *ll_remove_nth_node(list_t* list, uint_t n)
{
	if (!list || !list->head)
		return NULL;

	if (n > list->size - 1)
		n = list->size - 1;

	node_t *prev = NULL, *curr = list->head;

	while (n > 0) {
		prev = curr;
		curr = curr->next;
		n--;
	}

	if (prev == NULL)
		list->head = curr->next;
	else
		prev->next = curr->next;

	list->size--;
	return curr;
}

// Function that  deallocates the memory used by a list
// Credits: https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04
void ll_free(list_t** pp_list)
{
	node_t* currNode;
	if (!pp_list || !*pp_list)
		return;

	while ((*pp_list)->size > 0) {
		currNode = ll_remove_nth_node(*pp_list, 0);
		free(currNode->data);
		currNode->data = NULL;
		free(currNode);
		currNode = NULL;
	}

	free(*pp_list);
	*pp_list = NULL;
}

// Function that  creates a hash for a string
// Credits: http://www.cse.yorku.ca/~oz/hash.html
uint_t hash_function_string(void *a)
{
	unsigned char *puchar_a = (unsigned char*) a;
	int64_t hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */
	return hash;
}

// Function that  creates a hashtable
hashtable_t * ht_create(uint_t hmax, uint_t (*hash_function)(void*),
						int (*compare_function)(void*, void*))
{
	hashtable_t *ht = malloc(sizeof(hashtable_t));
	DIE(!ht, MALLOC_FAILED);
	ht->buckets = malloc(hmax * sizeof(list_t *));
	DIE(!ht->buckets, MALLOC_FAILED);

	ht->hmax = hmax;
	ht->size = 0;
	ht->hash_function = hash_function;
	ht->compare_function = compare_function;

	for (uint_t i = 0; i < hmax; i++)
		ht->buckets[i] = ll_create(sizeof(info_t));

	return ht;
}

// Function that  checks if a hashtable has a specified key
int ht_has_key(hashtable_t *ht, void *key)
{
	// Get the position of the bucket
	uint_t i = ht->hash_function(key) % ht->hmax;

	node_t *aux = ht->buckets[i]->head;

	// Iterate through the bucket
	while (aux) {
		// Compare the keys
		int cmp = ht->compare_function(key, (*(info_t*)aux->data).key);
		if (!cmp)
			return 1;
		aux = aux->next;
	}
	return 0;
}

// Function that  gets the value stored at a specified key
void *ht_get(hashtable_t *ht, void *key)
{
	// Get the position of the bucket
	uint_t i = ht->hash_function(key) % ht->hmax;

	node_t *aux = ht->buckets[i]->head;

	// Iterate through the bucket
	while (aux) {
		int cmp = ht->compare_function(key, (*(info_t*)aux->data).key);
		if (!cmp)
			return (*(info_t*)aux->data).value;
		aux = aux->next;
	}
	return NULL;
}

// Function that  puts a new entry associated with a specified key
void ht_put(hashtable_t *ht, void *key, uint_t key_size,
			void *value, uint_t value_size)
{
	info_t new_data;

	// Place the new key
	new_data.key = malloc(key_size);
	DIE(!new_data.key, MALLOC_FAILED);
	memcpy(new_data.key, key, key_size);

	// Place the new value
	new_data.value = malloc(value_size);
	DIE(!new_data.value, MALLOC_FAILED);
	memcpy(new_data.value, value, value_size);

	// Add the new data into the bucket
	uint_t i = ht->hash_function(key) % ht->hmax;
	ll_add_nth_node(ht->buckets[i], 0, &new_data);
	ht->size++;

	// Resize the hashtable if the load factor is above 1
	if (ht->size - 1 == ht->hmax)
		ht_resize(ht);
}

// Function that  removes the entry associated with a specified key
void ht_remove_entry(hashtable_t *ht, void *key, int type)
{
	// Get the position of the bucket
	uint_t i = ht->hash_function(key) % ht->hmax;

	// Iterate through the bucket until the entry is found
	node_t *aux = ht->buckets[i]->head;
	int pos = 0;
	while (aux) {
		int cmp = ht->compare_function(key, (*(info_t*)aux->data).key);
		if (!cmp) {
			// Free the memory occupied by the entry
			node_t *removed = ll_remove_nth_node(ht->buckets[i], pos);
			free((*(info_t*)aux->data).key);

			// Check if an entire book has to be removed
			if (!type) {
				book_t *details = (*(info_t*)aux->data).value;
				ht_free(details->content);
			}

			free((*(info_t*)aux->data).value);
			free(removed->data);
			free(removed);
			ht->size--;
			return;
		}
		pos++;
		aux = aux->next;
	}
}

// Function that resizes a hashtable that has a load factor above 1
void ht_resize(hashtable_t *ht)
{
	// Create a resized hashtable
	hashtable_t *new_ht = ht_create(ht->hmax * 2, ht->hash_function,
									ht->compare_function);
	for (uint_t i = 0; i < ht->hmax; i++) {
		if (ht->buckets[i]->head) {
			node_t *aux = ht->buckets[i]->head;
			while (aux) {
				ht_put(new_ht, (*(info_t*)aux->data).key,
					   sizeof((*(info_t*)aux->data).key),
					   (*(info_t*)aux->data).value,
					   sizeof((*(info_t*)aux->data).value));
					   aux = aux->next;
			}
		}
	}
	// Place the new hashtable into the old one
	ht = new_ht;
	ht_free(new_ht);
}

// Function that  frees the memory occupied by a hashtable
void ht_free(hashtable_t *ht)
{
	for (uint_t i = 0; i < ht->hmax; i++) {
		if (ht->buckets[i]->head) {
			node_t *aux = ht->buckets[i]->head;
			while (aux) {
				// Remove the data of each entry
				free((*(info_t*)aux->data).key);
				free((*(info_t*)aux->data).value);
				aux = aux->next;
			}
		}
		ll_free(&ht->buckets[i]);
	}
	free(ht->buckets);
	free(ht);
}
