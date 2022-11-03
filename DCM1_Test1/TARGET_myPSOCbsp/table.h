/*
 * table.h
 *
 *  Created on: Oct 15, 2022
 *      Author: Noura Bayat
 */

#ifndef TARGET_MYPSOCBSP_TABLE_H_
#define TARGET_MYPSOCBSP_TABLE_H_

#include <stdlib.h>
#include <string.h>

// Declaring Global Variables
#define ID_SIZE 20
extern unsigned int table_size;
extern struct node *hash_table;

extern char HashValue[20];

// Declaring Function

struct node
{
	char id[ID_SIZE];
	void *data;
	unsigned int data_size;
};

/*
 * Initializes table
 *
 * Takes size as parameter
 *
 * Returns pointer to start of table array
 */
struct node *initialize_table(int table_size);

/*
 * Adds a new node and initializes its data
 *
 * Takes the hash table pointer, hash table size, pointer to data, sizeof data type, and ID string
 *
 * Returns pointer to data inside the hash table
 *
 */
void *add_node(struct node *hash_table, unsigned int table_size, void *data, int data_size, char *data_id);

/*
 * Adds a new node and does not initialize the data
 *
 * Takes the hash table pointer, hash table size, sizeof data type, and ID string
 *
 * Returns pointer to data inside the hash table
 *
 */

void *allocate_node(struct node *hash_table, unsigned int table_size, int data_size, char *data_id);

/*
 * Performs a hash on the given string
 *
 * Takes a string as argument, as well as hash table size
 *
 * Returns integer result of the hash
 *
 * yoinked from http://www.cse.yorku.ca/~oz/hash.html
 *
 */
unsigned long int hash_string(char *str, unsigned int size);

/*
 * Returns pointer to node element
 *
 * Takes hash table
 *
 */
struct node *find_node(struct node *hash_table, unsigned int table_size, char *data_id);

#endif /* TARGET_MYPSOCBSP_TABLE_H_ */
