#pragma once
#include <iostream>
#include <exception>


template<class KeyType, class ValType>
class RBNode {
private:

	const KeyType key;
	const ValType value;
	bool color;
	RBNode<KeyType, ValType> *left;
	RBNode<KeyType, ValType> *right;
	RBNode<KeyType, ValType> *parent;

public:

	// Constants
	static const bool RED = false;
	static const bool BLACK = true;

	// C'tor
	RBNode(const KeyType key, const ValType value) : key(key), value(value), color(RED), left(NULL), right(NULL), parent(NULL) {};

	// Getters
	const KeyType	get_key()	const { return this->key; }
	const ValType	get_value()	const { return this->value; }
	bool			get_color()	const { return this->color; }
	bool			isBlack()	const { return this->color == BLACK; }
	RBNode<KeyType, ValType>*  get_left()	const { return this->left; }
	RBNode<KeyType, ValType>*  get_right()	const { return this->right; }
	RBNode<KeyType, ValType>*  get_parent()	const { return this->parent; }

	// Setters
	void set_color(const bool color)   { this->color = color; }
	void set_left(RBNode<KeyType, ValType>* node)  { this->left = node; }
	void set_right(RBNode<KeyType, ValType>* node) { this->right = node; }
	void set_parent(RBNode<KeyType, ValType>* node) { this->parent = node; }

};


template<class KeyType, class ValType>
class RBTree {
private:

	// Root Node
	RBNode<KeyType, ValType>* root;

	// Private Functions
	RBNode<KeyType, ValType>* GetSuccessor(const RBNode<KeyType, ValType>* node) const;
	RBNode<KeyType, ValType>* GetPredecessor(const RBNode<KeyType, ValType>* node) const;
	void LeftRotate(RBNode<KeyType, ValType>* node);
	void RightRotate(RBNode<KeyType, ValType>* node);
	void InsertFixUp(RBNode<KeyType, ValType>* node);
	void DeleteFixUp(RBNode<KeyType, ValType>* node);
	RBNode<KeyType, ValType>* GetNode(const KeyType &key) const;
	RBNode<KeyType, ValType>* GetMinNode() const;
	RBNode<KeyType, ValType>* GetMaxNode() const;

public:

	// C'tor
	RBTree() : root(NULL) {};

	// Red-black tree functions
	void Insert(const KeyType key, const ValType value);
	void Delete(const KeyType &key);
	
	// Get functions
	ValType Get(const KeyType &key) const;
	ValType GetMin() const;
	ValType GetMax() const;

};

class KeyNotFoundException : public std::exception {};