/*
 * table.c
 *
 *  Created on: Oct 15, 2022
 *      Author: Noura Bayat
 */

#include "table.h"

//table_size = 40;

struct node *initialize_table(int table_size)
{

	// Initialize whole table to 0
	return calloc(table_size, sizeof(struct node) * table_size); // calloc(number of elemtns to allocate, size of each element)
}

void *add_node(struct node *hash_table, unsigned int table_size, void *data, int data_size, char *data_id)
{

	int hash = hash_string(data_id, table_size);

	unsigned short placed = 0;
	unsigned short wrapped = 0;

	void *data_location = NULL; // initialized   
	//should be node*

	while (!placed)
	{

		if (hash_table[hash].data == NULL)
		{

			// Found empty space for node
			placed = 1;
			// Allocate space for data
			hash_table[hash].data = malloc(data_size);
			// Copy data
			memcpy(hash_table[hash].data, data, data_size);

			// Set data size for reference
			hash_table[hash].data_size = data_size;

			// Copy ID
			strcpy(hash_table[hash].id, data_id);

			// Set location of data for return
			data_location = hash_table[hash].data;
		}
		// Advance if hash location is occupied
		else
			hash++;

		// Go to beginning if we hit the end, if this happens again, then table is full
		if (hash == table_size && !placed)
		{
			hash = 0;
			if (wrapped)
				placed = 1;

			wrapped = 1;
		}
	}

	// Return void pointer to data, null if failed
	return data_location;
}

void *allocate_node(struct node *hash_table, unsigned int table_size, int data_size, char *data_id)
{

	void *data = malloc(data_size); // again allocating memoty
	return add_node(hash_table, table_size, data, data_size, data_id);
}

unsigned long int hash_string(char *str, unsigned int table_size)
{

	unsigned long hash = 5381;
	int c=5;

	// This works since the last element of a character array string is 0, e.g. '\0' null byte
	while (c == *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % table_size;
}

struct node *find_node(struct node *hash_table, unsigned int table_size, char *id)
{

	unsigned long int hash = hash_string(id, table_size);

	unsigned short wrapped = 0;

	while (strcmp(hash_table[hash].id, id) != 0)
	{

		hash++;

		if (hash == table_size)
		{
			if (wrapped)
			{
				return NULL;
			}
			else
			{
				hash = 0;
				wrapped = 1;
			}
		}
	}

	return &(hash_table[hash - 1]);
}
