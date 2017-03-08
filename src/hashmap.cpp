#include <iostream>
#include <exception>
#include "hashmap.h"

// HashEntry C'tor
// Initialize the key-value pair.
template <class KeyType, class ValType>
HashEntry<KeyType,ValType>::HashEntry(const KeyType& key, const ValType& value) : key(key), value(value) {
}

// HashMap C'tor
// Initialize array of pointers to HashEntry objects of size TABLE_SIZE.
// Also initialize the TABLE_SIZE const.
template <class KeyType, class ValType>
HashMap<KeyType, ValType>::HashMap(const size_t table_size) : TABLE_SIZE(table_size) {

	this->table = new HashEntry<KeyType, ValType>*[this->TABLE_SIZE];
	for (size_t i = 0; i < this->TABLE_SIZE; i++) {
		this->table[i] = NULL;
	}

}

// HashMap D'tor
// Delete all HashEntry objects and the table array.
template <class KeyType, class ValType>
HashMap<KeyType, ValType>::~HashMap() {
	
	for (size_t i = 0; i < this->TABLE_SIZE; i++) {
		if (this->table[i] != NULL) {
			delete this->table[i];
		}
	}
	delete[] this->table;
}


// HashMap Hash Function
// A simple division method is used as the base hash function.
// Afer the division is done, the function searches for an unused cell or
// a cell with the desired key in the table ("Open Addressing").
template <class KeyType, class ValType>
size_t HashMap<KeyType, ValType>::HashFunction(const KeyType &key) const {
	
	size_t hash = int(key) % this->TABLE_SIZE;

	while (this->table[hash] != NULL && this->table[hash]->get_key() != key) {
		
		hash = (hash + 1) % this->TABLE_SIZE;
	}

	return hash;

}

// HashMap Insert Function
// Uses HashFunction to find an unused cell or a cell with the desired key if it exists.
// In case it doesn't exist, create a new HashEntry with the key-value pair.
// Otherwise, change the cell value to the new desired value.
template <class KeyType, class ValType>
void HashMap<KeyType, ValType>::Insert(const KeyType &key, const ValType &value) {

	size_t hash = this->HashFunction(key);
	if (this->table[hash] == NULL) {
		this->table[hash] = new HashEntry<KeyType, ValType>(key, value);
	} else {
		delete this->table[hash];
		this->table[hash] = new HashEntry<KeyType, ValType>(key, value);
	}

}

// HashMap HasKey Function
// Uses HashFunction to find a cell with the desired key.
// If it exists return True, otherwise return False.
template <class KeyType, class ValType>
bool HashMap<KeyType, ValType>::HasKey(const KeyType &key) const {

	size_t hash = this->HashFunction(key);
	return this->table[hash] != NULL;

}

// HashMap Get Function
// Uses HashFunction to find a cell with the desired key.
// If it exists, return its HashEntry value.
// If not, return NULL.
template <class KeyType, class ValType>
const ValType& HashMap<KeyType, ValType>::Get(const KeyType &key) const {

	size_t hash = this->HashFunction(key);
	if (this->table[hash] == NULL) throw KeyNotFoundException();
	return this->table[hash]->get_value();

}

// HashMap Remove Function
// Uses HashFunction to find a cell with the desired key.
// If it exists, delete its HashEntry object and change the pointer to NULL.
template <class KeyType, class ValType>
void HashMap<KeyType, ValType>::Remove(const KeyType &key) {

	size_t hash = this->HashFunction(key);
	if (this->table[hash] == NULL) throw KeyNotFoundException();
	delete this->table[hash];
	this->table[hash] = NULL;

}