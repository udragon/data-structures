#include <iostream>
#include <exception>
#include "rbtree.h"


// Red-Black Tree Left Rotate Function
// Gets a pointer to a Red-Black node, and rotate it with its right child.
template<class KeyType, class ValType>
void RBTree<KeyType, ValType>::LeftRotate(RBNode<KeyType, ValType>* node) {

	RBNode<KeyType, ValType>* rnode = node->get_right();
	if (rnode == NULL) return; // Right child must exist on right rotation.

	node->set_right(rnode->get_left());
	if (rnode->get_left() != NULL) rnode->get_left()->set_parent(node);
	rnode->set_parent(node->get_parent());

	if (node->get_parent() == NULL)	this->root = rnode;
	else if (node == node->get_parent()->get_left()) node->get_parent()->set_left(rnode);
	else node->get_parent()->set_right(rnode);
	
	rnode->set_left(node);
	node->set_parent(rnode);

}


// Red-Black Tree Right Rotate Function
// Gets a pointer to a Red-Black node, and rotate it with its left child.
template<class KeyType, class ValType>
void RBTree<KeyType, ValType>::RightRotate(RBNode<KeyType, ValType>* node) {

	RBNode<KeyType, ValType>* lnode = node->get_left();
	if (lnode == NULL) return; // Left child must exist on right rotation.

	node->set_left(lnode->get_right());
	if (lnode->get_right() != NULL) lnode->get_right()->set_parent(node);
	lnode->set_parent(node->get_parent());

	if (node->get_parent() == NULL)	this->root = lnode;
	else if (node == node->get_parent()->get_right()) node->get_parent()->set_right(lnode);
	else node->get_parent()->set_left(lnode);

	lnode->set_right(node);
	node->set_parent(lnode);

}


// Red-Black Tree Insert Function
// Gets key and value, create a node and attach it to the tree.
template<class KeyType, class ValType>
void RBTree<KeyType, ValType>::Insert(const KeyType key, const KeyType value) {

	RBNode<KeyType, ValType>* node = new RBNode<KeyType, ValType>(key, value);
	RBNode<KeyType, ValType>* x = this->root;
	RBNode<KeyType, ValType>* y = NULL;

	// Search for a suitable node to attach to
	while (x != NULL) {
		y = x;
		if (node->get_key() < x->get_key()) x = x->get_left();
		else x = x->get_right();
	}

	// Attach the new node to the tree
	node->set_parent(y);
	if (y == NULL) this->root = node; // Tree is empty
	else if (node->get_key() < y->get_key()) y->set_left(node);
	else y->set_right(node);

	// Fix-up tree colors
	this->InsertFixUp(node);

}


// Red-Black Tree Insert Fix-up Function
// Gets the changed node, and fix the tree colors accourdingly.
template<class KeyType, class ValType>
void RBTree<KeyType, ValType>::InsertFixUp(RBNode<KeyType, ValType>* node) {

	RBNode<KeyType, ValType>* p = node->get_parent();
	RBNode<KeyType, ValType>* y = NULL;

	while (p != NULL && p->get_color() == RBNode<KeyType, ValType>::RED) {
		if (p == p->get_parent()->get_left()) {

			y = p->get_parent()->get_right();
			if (y != NULL && y->get_color() == RBNode<KeyType, ValType>::RED) {
				p->set_color(RBNode<KeyType, ValType>::BLACK);
				y->set_color(RBNode<KeyType, ValType>::BLACK);
				p->get_parent()->set_color(RBNode<KeyType, ValType>::RED);
				node = p->get_parent();
			}
			else {
				if (node == p->get_right()) {
					node = p;
					this->LeftRotate(node);
				}

				p->set_color(RBNode<KeyType, ValType>::BLACK);
				p->get_parent()->set_color(RBNode<KeyType, ValType>::RED);
				this->RightRotate(p->get_parent());
			}
		}
		else {

			y = p->get_parent()->get_left();
			if (y != NULL && y->get_color() == RBNode<KeyType, ValType>::RED) {
				p->set_color(RBNode<KeyType, ValType>::BLACK);
				y->set_color(RBNode<KeyType, ValType>::BLACK);
				p->get_parent()->set_color(RBNode<KeyType, ValType>::RED);
				node = p->get_parent();
			}
			else {
				if (node == p->get_left()) {
					node = p;
					this->LeftRotate(node);
				}
			
				p->set_color(RBNode<KeyType, ValType>::BLACK);
				p->get_parent()->set_color(RBNode<KeyType, ValType>::RED);
				this->RightRotate(p->get_parent());
			}
		}

	}

	this->root->set_color(RBNode<KeyType, ValType>::BLACK);
}


// Red-Black Tree Delete Function
// Gets a key and remove the node associated with that key.
template<class KeyType, class ValType>
void RBTree<KeyType, ValType>::Delete(const KeyType &key) {

	RBNode<KeyType, ValType>* node = this->GetNode(key);
	
	RBNode<KeyType, ValType>* x = NULL;
	RBNode<KeyType, ValType>* y = NULL;

	if (node->get_left() == NULL || node->get_right() == NULL) y = node;
	else y = this->GetSuccessor(node);

	if (y->get_left() != NULL) x = y->get_left();
	else x = y->get_right();

	if (x != NULL) x->set_parent(y->get_parent());

	if (y->get_parent() == NULL) this->root = x;
	else if (y == y->get_parent()->get_left()) y->get_parent()->set_left(x);
	else y->get_parent()->set_right(x);

	if (y != node) {
		// Place y instead of node
		y->set_left(node->get_left());
		y->set_right(node->get_right());
		y->set_parent(node->get_parent());
		y->get_left()->set_parent(y);
		y->get_right()->set_parent(y);
		if (y->get_parent()->get_right() == node) y->get_parent()->set_right(y);
		else y->get_parent()->set_left(y);
	}

	if (y->get_color() == RBNode<KeyType, ValType>::BLACK) this->DeleteFixUp(x);

}


// Red-Black Tree Delete Fix-up Function
// Gets the changed node, and fix the tree colors accourdingly.
template<class KeyType, class ValType>
void RBTree<KeyType, ValType>::DeleteFixUp(RBNode<KeyType, ValType>* node) {

	RBNode<KeyType, ValType>* w = NULL;

	while (node != this->root && node->get_color() == RBNode<KeyType, ValType>::BLACK) {
		if (node == node->get_parent()->get_left()) {

			w = node->get_parent()->get_right();

			if (w != NULL && w->get_color() == RBNode<KeyType, ValType>::RED){
				w->set_color(RBNode<KeyType, ValType>::BLACK);
				node->get_parent()->set_color(RBNode<KeyType, ValType>::RED);
				this->LeftRotate(node->get_parent());
				w = node->get_parent()->get_right();
			}

			if (w != NULL && w->get_left()->get_color() == RBNode<KeyType, ValType>::BLACK && w->get_right()->get_color() == RBNode<KeyType, ValType>::BLACK) {
				w->set_color(RBNode<KeyType, ValType>::RED);
				node = node->get_parent();
			}
			else  {
				if (w != NULL && w->get_right()->get_color() == RBNode<KeyType, ValType>::BLACK) {
					w->get_left()->set_color(RBNode<KeyType, ValType>::BLACK);
					w->set_color(RBNode<KeyType, ValType>::RED);
					this->RightRotate(w);
					w = node->get_parent()->get_right();
				}

				if (w != NULL ) w->set_color(node->get_parent()->get_color());
				node->get_parent()->set_color(RBNode<KeyType, ValType>::BLACK);
				if (w != NULL) w->get_right()->set_color(RBNode<KeyType, ValType>::BLACK);
				this->LeftRotate(node->get_parent());
				node = this->root;
			}

		}
		else {

			w = node->get_parent()->get_left();

			if (w != NULL && w->get_color() == RBNode<KeyType, ValType>::RED){
				w->set_color(RBNode<KeyType, ValType>::BLACK);
				node->get_parent()->set_color(RBNode<KeyType, ValType>::RED);
				this->RightRotate(node->get_parent());
				w = node->get_parent()->get_left();
			}

			if (w != NULL && w->get_right()->get_color() == RBNode<KeyType, ValType>::BLACK && w->get_left()->get_color() == RBNode<KeyType, ValType>::BLACK) {
				w->set_color(RBNode<KeyType, ValType>::RED);
				node = node->get_parent();
			}
			else {
				if (w != NULL && w->get_left()->get_color() == RBNode<KeyType, ValType>::BLACK) {
					w->get_right()->set_color(RBNode<KeyType, ValType>::BLACK);
					w->set_color(RBNode<KeyType, ValType>::RED);
					this->LeftRotate(w);
					w = node->get_parent()->get_left();
				}

				if (w != NULL) w->set_color(node->get_parent()->get_color());
				node->get_parent()->set_color(RBNode<KeyType, ValType>::BLACK);
				if (w != NULL) w->get_left()->set_color(RBNode<KeyType, ValType>::BLACK);
				this->RightRotate(node->get_parent());
				node = this->root;
			}

		}
	}

	node->set_color(RBNode<KeyType, ValType>::BLACK);

}


// Red-Black Tree GetNode Function
// Search the tree for a key, and return its RBNode.
template<class KeyType, class ValType>
RBNode<KeyType, ValType>* RBTree<KeyType, ValType>::GetNode(const KeyType &key) const {

	RBNode<KeyType, ValType>* x = this->root;

	while (x != NULL && x->get_key() != key) {
		if (x->get_key() > key) x = x->get_left();
		else x = x->get_right();
	}

	return x;

}


// Red-Black Tree Get Function
// Search the tree for a key. If it exists, return its value.
// Otherwise, throw an exception.
template<class KeyType, class ValType>
ValType RBTree<KeyType, ValType>::Get(const KeyType &key) const {

	RBNode<KeyType, ValType>* x = this->GetNode(key);
	if (x == NULL) throw KeyNotFoundException();
	return x->get_value();

}


// Red-Black Tree GetMin Function
// Returns the leftmost node in tree.
template<class KeyType, class ValType>
RBNode<KeyType, ValType>* RBTree<KeyType, ValType>::GetMinNode() const {
	RBNode<KeyType, ValType>* x = this->root;
	while (x->get_left() != NULL) x = x->get_left();
	return x;
}

template<class KeyType, class ValType>
ValType RBTree<KeyType, ValType>::GetMin() const {
	return this->GetMinNode()->get_value();
}

// Red-Black Tree GetMax Function
// Returns the rightmost node in tree.
template<class KeyType, class ValType>
RBNode<KeyType, ValType>* RBTree<KeyType, ValType>::GetMaxNode() const {
	RBNode<KeyType, ValType>* x = this->root;
	while (x->get_right() != NULL) x = x->get_right();
	return x;
}

template<class KeyType, class ValType>
ValType RBTree<KeyType, ValType>::GetMax() const {
	return this->GetMaxNode()->get_value();
}

// Red-Black Tree GetSuccessor Function
// Returns the successor node of a given node.
template<class KeyType, class ValType>
RBNode<KeyType, ValType>* RBTree<KeyType, ValType>::GetSuccessor(const RBNode<KeyType, ValType>* node) const {
	RBNode<KeyType, ValType>* y = NULL;
	RBNode<KeyType, ValType>* x = NULL;

	if (node->get_right() != NULL) {
		x = node->get_right();
		while (x->get_left() != NULL) x = x->get_left();
		return x;
	}
	y = node->get_parent();
	while (y != NULL && node == y->get_right())  {
		node = y;
		y = y->get_parent();
	}
	return y;
}

// Red-Black Tree GetPredecessor Function
// Returns the predecessor node of a given node.
template<class KeyType, class ValType>
RBNode<KeyType, ValType>* RBTree<KeyType, ValType>::GetPredecessor(const RBNode<KeyType, ValType>* node) const {
	RBNode<KeyType, ValType>* y = NULL;
	RBNode<KeyType, ValType>* x = NULL;

	if (node->get_left() != NULL) {
		x = node->get_left();
		while (x->get_right() != NULL) x = x->get_right();
		return x;
	}
	y = node->get_parent();
	while (y != NULL && node == y->get_left())  {
		node = y;
		y = y->get_parent();
	}
	return y;
}





