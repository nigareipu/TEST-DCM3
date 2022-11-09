/*
 * table.h
 *
 *  Created on: Oct 15, 2022
 *      Author: Noura Bayat
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef TARGET_MYPSOCBSP_TABLE_H_
#define TARGET_MYPSOCBSP_TABLE_H_


#define ID_SIZE 20



/* Reference to old protocol
 typedef struct {
	 uint8_t id; ///< Register ID that is exposed to the bus.
	 uint8_t size; ///<  Size of the register in bytes.
	 UCG2_REGTYPE type; ///< Type of data the register is intended to hold.
	 bool computed; ///< Is the value of this register computed when requested?
	 void * value; ///< Pointer to the value of the register, for a stored-value register.
	 bool freeable; ///< Should the thing this pointer points to be freed on destruction?
	 UCG2_REG_CB_RET_TYPE (*reg_callback)(void); ///< If this is a computed register, the function to call.
	 bool readable; ///< Is this register readable?
	 bool writeable; ///< Is this register writeable?
	 int (*reg_wrt_callback)(UCG2_REG_CB_ARG_TYPE); ///< If this is a computed register and it is written to, the function to call.
	 bool strict; ///< Enable strict mode, where writes must be the exact right size to be valid and cannot be padded.
	 bool cached; ///< Enable caching of computed values.  This requires both a callback and a variable pointer to be present.
	 uint16_t cache_timeout; ///< Time in ms that a cached value is valid.
	 uint32_t computed_time; ///< Some time in ms that the cached value was computed at.
 } UCG2_REGISTER;
 */

enum NODE_TYPE {T_UINT32, T_UINT16, T_UINT8, T_INT32, T_INT16, T_INT8, T_FLOAT, T_BOOLEAN, T_CHAR, T_NODE};

struct NODE_CB_TYPE{
	enum NODE_TYPE data_type;
	void* data;
	unsigned int data_size;
};


// This is a structure of a node in our hash table
struct TNODE{

	//--- These set by allocate_node and add_node:
	char id[ID_SIZE]; // String identifying entry, must be unique
	unsigned int data_size; // Total size of allocated memeory for node's data field
	void* data; // Void pointer to data field
	enum NODE_TYPE data_type; // enum for data type of entry

	//--- These must be set by user after call:
	bool is_array; // Boolean to track whether data is an array
	bool readable;
	bool writeable;
	bool executable;

	// These are optional depending on boolean settings
	struct NODE_CB_TYPE (*read_cb); // read_cb and write_cb must be set if executable is true
	struct NODE_CB_TYPE (*write_cb);
	unsigned int element_size; // If array, sizeof each element in array

};


/*
 * Initializes table
 *
 * Takes size as parameter
 *
 * Returns pointer to start of table array
 */
struct TNODE* initialize_table(int table_size);

/*
 * Adds a new node and initializes its data
 *
 * Takes the hash table pointer, hash table size, pointer to data, sizeof data type, and ID string
 *
 * Returns pointer to data inside the hash table
 *
 */
struct TNODE* add_node(struct TNODE* hash_table, unsigned int table_size, void* data, int data_size, char* data_id);

/*
 * Adds a new node and does not initialize the data
 *
 * Takes the hash table pointer, hash table size, sizeof data type, and ID string
 *
 * Returns pointer to data inside the hash table
 *
 */

void* allocate_node(struct TNODE* hash_table, unsigned int table_size, int data_size, char* data_id);

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
unsigned long int hash_string(char* str, unsigned int size);

/*
 * Returns pointer to node element
 *
 * Takes hash table
 *
 */
struct TNODE* find_node(struct TNODE* hash_table, unsigned int table_size, char *id);

// Not implemented probably best to just
//int resize_table(struct TNODE** hash_table, unsigned int table_size);

#endif /* TARGET_MYPSOCBSP_TABLE_H_ */
