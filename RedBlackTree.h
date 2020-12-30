#pragma once
#include<vector>
#include<map>
#include<iostream>
using std::vector;
using std::cout;
using std::endl;

class NodeT
{
public:
	int key;
	char value;
	NodeT* left;
	NodeT* right;
	NodeT* parent;
	
	bool isBlack;
	NodeT(int key, char val) : key(key), value(val), left(nullptr), right(nullptr), parent(nullptr), isBlack(false) { ; };

};

class RedBlackTree
{
public:
	RedBlackTree();
	RedBlackTree(const RedBlackTree& rbt);
	RedBlackTree& operator=(const RedBlackTree& rbt);
	~RedBlackTree();
	bool insert(int key, char val);
	bool remove(int key);
	bool search(int key);
	vector<char> search(int key1, int key2) const;
	vector<char> values() const;
	vector<int> keys() const;
	int size();
	NodeT* getRoot() const ;
	int height() const;

	void print() const;

private:
	NodeT* root;
	// record the size of the tree
	int count;
	// helper methods
	void leftRotation(NodeT* p);
	void rightRotation(NodeT* p);
	void copyTree(const NodeT* nd, NodeT*& p);
	void clear(NodeT* nd);

	NodeT* findNode (int key) const;
	NodeT* getPredecessor (NodeT* nd) const;
	void fixTree(NodeT* x, NodeT* xp, bool LoR);
	bool leftOrRight(NodeT* p);

	void searchHelper(NodeT* nd, vector<char>& v, int key1, int key2) const ;
	void valueHelper(NodeT* nd, vector<char>& v) const;
	void keyHelper(NodeT* nd, vector<int>& v) const ;
	int sizeHelper(NodeT* nd);

	void inOrderPrint(NodeT* nd) const;
	int height(NodeT* nd) const;
};


// RedBlackTree method implementations
