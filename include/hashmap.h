#pragma once
#include <iostream>
#include <exception>

// Hash Entry object used to store a key-value pair.
// Example:
//		HashEntry<int,int> e(1,10);
//		std::cout << e.get_value();
template <class KeyType, class ValType>
class HashEntry {

private:
	const KeyType &key;
	const ValType &value;

public:
	// C'tor
	HashEntry(const KeyType &key, const ValType &value);

	const KeyType& get_key() const { return key; }
	const ValType& get_value() const { return value; }

};

// Hash Map object is used to store a hash table of an arbitrary size.
// NOTICE! ValType must be hashable: custom objects should implement the int() operator.
// Example:
//		HashMap<int,int> m(128);
//		m.Insert(1,100);
//		std::cout << m.Get(1);
template <class KeyType, class ValType>
class HashMap {

private:
	const size_t TABLE_SIZE;
	HashEntry<KeyType, ValType>** table;

	size_t HashFunction(const KeyType &key) const;

public:
	// C'tor and D'tor
	HashMap(const size_t table_size);
	~HashMap();
	
	// Insert, remove and get functions
	void Insert(const KeyType &key, const ValType &value);
	void Remove(const KeyType &key);
	const ValType& Get(const KeyType &key) const;
	bool HasKey(const KeyType &key) const;

};

class KeyNotFoundException : public std::exception {};