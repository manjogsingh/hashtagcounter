#include "FibonacciHeap.h"

#include <iostream>

// MARK: Node defination

Node::Node(int v) {
	prev = this;
	next = this;
	child = nullptr;
	parent = nullptr;

	degree = 0;
	bChildCut = false;
	value = v;
}

// MARK: FibonacciHeap defination

FibonacciHeap::FibonacciHeap() {
	fHeap = nullptr;
}

FibonacciHeap::~FibonacciHeap() {
	if (fHeap) {
		_deleteHeap(fHeap);
	}
}

/*Adds a new element to the Max Fibonacci Heap*/
void FibonacciHeap::insert(int value) {
	Node* in = new Node(value);
	fHeap = _meld(fHeap, in);
	in = nullptr;
	delete in;
}

/*Melds two Heaps into one*/
void FibonacciHeap::meld(FibonacciHeap* otherHeap) {
	fHeap = _meld(fHeap, otherHeap->fHeap);
	otherHeap->fHeap = nullptr;
}

/*Increases the value of a Node by given input*/
void FibonacciHeap::increaseKey(Node* n, int iValue) {
	fHeap = _increaseKey(fHeap, n, iValue);
}

/*Returns the current Maximum value*/
int FibonacciHeap::getMaximum() {
	return fHeap->value;
}

/*Removes and returns the current Maximum value*/
int FibonacciHeap::removeMaximum() {
	if (fHeap) {
		Node* max = fHeap;
		fHeap = _removeMaximum(fHeap);
		int mValue = max->value;
		delete max;
		return mValue;
	}
	return -1;
}

Node* FibonacciHeap::_removeMaximum(Node* n) {
	_unParentAll(n->child);

	if (n->next == n) {
		n = n->child;
	} else {
		n->next->prev = n->prev;
		n->prev->next = n->next;

		n = _meld(n->next, n->child);
	}

	if (n == nullptr) return n;
	Node* trees[64] = {nullptr};

	while (true) {
		if (trees[n->degree] != nullptr) {
			Node* t = trees[n->degree];
			if (t == n) break;
			trees[n->degree] = nullptr;
			if (n->value > t->value) {
				t->prev->next = t->next;
				t->next->prev = t->prev;
				_addChild(n, t);
			} else {
				t->prev->next = t->next;
				t->next->prev = t->prev;

				if (n->next == n) {
					t->next = t->prev = t;
					_addChild(t, n);
					n = t;
				} else {
					n->prev->next = t;
					n->next->prev = t;
					t->next = n->next;
					t->prev = n->prev;
					_addChild(t, n);
					n = t;
				}
			}
			continue;
		} else {
			trees[n->degree] = n;
		}
		n = n->next;
	}
	Node* max = n;
	Node* start = n;
	do {
		if (n->value > max->value) max = n;
		n = n->next;
	} while (n != start);
	return max;
}

Node* FibonacciHeap::_meld(Node* a, Node* b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;
	if (b->value > a->value) {
		Node* temp = a;
		a = b;
		b = temp;
	}
	Node* aNext = a->next;
	Node* bPrev = b->prev;

	a->next = b;
	b->prev = a;

	aNext->prev = bPrev;
	bPrev->next = aNext;

	return a;
}

/*Performs the child cut operation*/
Node* FibonacciHeap::_cut(Node* heap, Node* n) {
	if (n->next == n) {
		n->parent->child = nullptr;
	} else {
		n->next->prev = n->prev;
		n->prev->next = n->next;
		n->parent->child = n->next;
	}
	n->next = n->prev = n;
	n->bChildCut = false;
	return _meld(heap, n);
}

Node* FibonacciHeap::_increaseKey(Node* heap, Node* n, int iValue) {
	if (n->value > iValue) return heap;
	n->value = iValue;
	if (n->parent) {
		if (n->value > n->parent->value) {
			heap = _cut(heap, n);
			Node* parent = n->parent;
			n->parent = nullptr;
			while (parent != nullptr && parent->bChildCut) {
				heap = _cut(heap, parent);
				n = parent;
				parent = n->parent;
				n->parent = nullptr;
			}
			if (parent != nullptr && parent->parent != nullptr)
				parent->bChildCut = true;
		}
	} else {
		if (n->value > heap->value) {
			heap = n;
		}
	}
	return heap;
}

/*Empties out a heap by cleaning up all references and memory*/
void FibonacciHeap::_deleteHeap(Node* n) {
	if (n) {
		Node* c = n;
		do {
			Node* d = c;
			c = c->next;
			_deleteHeap(d->child);
			delete d;
		} while (c != n);
	}
}

/*Adds a new child to a Node*/
void FibonacciHeap::_addChild(Node* parent, Node* child) {
	child->prev = child->next = child;
	child->parent = parent;
	parent->degree++;
	parent->child = _meld(parent->child, child);
}

/*Clears out parent pointer of a Node*/
void FibonacciHeap::_unParentAll(Node* n) {
	if (n == nullptr) return;
	Node* c = n;
	do {
		c->bChildCut = false;
		c->parent = nullptr;
		c = c->next;
	} while (c != n);
}