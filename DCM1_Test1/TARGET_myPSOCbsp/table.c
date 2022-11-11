/*
 * table.c
 *
 *  Created on: Oct 15, 2022
 *      Author: Noura Bayat
 */
#include "table.h"

/*
 * Initializes table
 *
 * Takes size as parameter
 *
 * Returns pointer to start of table array
 */
struct TNODE* initialize_table(int table_size){

	// Initialize whole table to 0
	return calloc(table_size, sizeof(struct TNODE)*table_size);
}


 /*
 * Adds a new node and initializes its data
 *
 * Takes the hash table pointer, hash table size, pointer to data, sizeof data type, and ID string
 *
 * Returns pointer to data inside the hash table
 *
 */
struct TNODE* add_node(struct TNODE* hash_table, unsigned int table_size, void* data, int data_size, char* data_id){


	int hash = hash_string(data_id, table_size);

	bool placed = false;
	bool wrapped = false;

	void* data_location = NULL;

	while (!placed){
		if (hash_table[hash].data == NULL){

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
		if (hash == table_size && !placed){
			hash = 0;
			if (wrapped)
				placed = true;

			wrapped = true;
		}
	}

	// Return void pointer to data, null if failed
	return &(hash_table[hash]);

}

/*
 * Adds a new node and does not initialize the data
 *
 * Takes the hash table pointer, hash table size, sizeof data type, and ID string
 *
 * Returns pointer to data inside the hash table
 *
 */
void* allocate_node(struct TNODE* hash_table, unsigned int table_size, int data_size, char* data_id){

	void* data = malloc(data_size);
	return add_node(hash_table, table_size, data, data_size, data_id);

}

/*
 * Performs a hash on the given string
 *
 * Takes a string as argument, as well as hash table size
 *
 * Returns integer result of the hash
 *
 *
 * yoinked from http://www.cse.yorku.ca/~oz/hash.html
 *
 */
unsigned long int hash_string(char* str, unsigned int table_size){


	unsigned long hash = 5381;
	int c;

	// This works since the last element of a character array string is 0, e.g. '\0' null byte
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % table_size;
}

struct TNODE* find_node(struct TNODE* hash_table, unsigned int table_size, char* id){

	unsigned long int hash = hash_string(id, table_size);

	bool wrapped = false;

	while (strncmp(hash_table[hash].id, id, ID_SIZE) != 0){

		hash++;

		if (hash == table_size){
			if (wrapped){
				return NULL;
			}
			else{
				hash = 0;
				wrapped = true;
			}
		}
	}

	return &(hash_table[hash]);


}


/* Not implemented
unsigned int resize_table(struct TNODE** hash_table, unsigned int table_size){

	unsigned int new_size = (unsigned int)(table_size * 1.5);
	struct TNODE* new_table = calloc(sizeof(struct node)*new_size);

	for (int i = 0; i < table_size; i++){

		// If element contains data
		if ((*hash_table[i]).data != NULL){
			add_node(new_table, new_size, &((*hash_table)[i].data), (*hash_table)[i].data_size, (*hash_table)[i].id);
		}



	}

}
*/

void update_node(struct TNODE* hash_table, unsigned int table_size, char* id, char* buffer)
{
	struct TNODE* new_node;

	char* readBuffer;
	readBuffer=buffer;
	int read_int;
	float read_float;
	new_node = find_node(hash_table, table_size, id);
	//printf("inside Update node\n\r");

	if(new_node->data_type == T_FLOAT){
		read_float=atof(readBuffer);
		//printf("inside Update node, printing float: %f\n\r",read_float);
		float* new_data=new_node->data;
		*new_data=read_float;
	}
	else if(new_node->data_type == T_UINT8){
		read_int=atoi(readBuffer);
		//printf("inside Update node, printing int: %i\n\r",read_int);
		int* new_data=new_node->data;
		*new_data=read_int;
	}
	else if(new_node->data_type == T_BOOLEAN){
		bool* new_bool=new_node->data;
			if (strncmp(readBuffer, "true",4)==0){
			*new_bool=true;
			}
			else {
				*new_bool=false;
			}
		//printf("address of Boolean: %p\n\r", new_bool);
		//printf("inside Update node, printing Boolean: %d\n\r", *new_bool);

	}

}

