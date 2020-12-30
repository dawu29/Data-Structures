#include "RedBlackTree.h"

// RedBlackTree method implementations
// defualt constructor
RedBlackTree::RedBlackTree()
{
	root = nullptr;
	count = 0;
}

RedBlackTree::RedBlackTree(const RedBlackTree& rbt)
{
	// makes an empty tree if the parameter is an empty tree
	if (rbt.root == nullptr) {
		root = nullptr;
		count = 0;
	}
	else {
		root = nullptr;
		// in the first call, assign object's root with bst.root
		copyTree(rbt.root, root);
	}
}

// overloaded assignment operator
RedBlackTree& RedBlackTree :: operator=(const RedBlackTree& rbt)
{	
	if (this != &rbt) {
		clear(root);
		copyTree(rbt.root, root);
	}
	return *this;
}

// deep copy helper method 
// PARAM: nd is the current node to be copied(starts with root of the parameter), p is the node to be assigned
void RedBlackTree::copyTree(const NodeT* nd, NodeT*& p) {
	if (nd != nullptr) {
		p = new NodeT(nd->key, nd->value);
		// assign p->left with nd->left
		copyTree(nd->left, p->left);
		if (p->left != nullptr) {
			p->left->parent = p; // assign parent poinyter
		}
		copyTree(nd->right, p->right);
		if (p->right != nullptr) {
			p->right->parent = p;
		}
	}
}

RedBlackTree::~RedBlackTree() {
	clear(root);
}

//helper method deleting the tree
void RedBlackTree::clear(NodeT* nd)
{
	if (nd != nullptr) {
		clear(nd->left);
		clear(nd->right);
		delete nd;
	}
}

// the same as the code discussed in class lecture
bool RedBlackTree::insert(int key, char val) {
	NodeT* newNode = new NodeT(key, val);
	newNode->parent = root;
	NodeT* next = root;
	NodeT* uncle; //newNode's parent's sibliing 
	// the case where the tree is empty
	if (root == nullptr) {
		root = newNode;
		root->isBlack = true;
		return true;
	}
	else { 
		// Find parent of new node
		while (next != nullptr) {
			newNode->parent = next;
			// return false if the inserted item's key is already existed in the tree.
			if (key == newNode->parent->key) {
				return false;
			}
			else if (key < newNode->parent->key) {
				next = newNode->parent->left;
			}
			else {
				next = newNode->parent->right;
			}
		}
		// insert new node
		if (key < newNode->parent->key) {
			newNode->parent->left = newNode;
		}
		else {
			newNode->parent->right = newNode;
		}
	}
	//RBT insert fix starts here
	newNode->isBlack = false;
	//iterates untill the root or a black parent is reached
	while (newNode != root && newNode->parent->isBlack == false) {
		// newNode's parent is a left child of grandparent
		if (newNode->parent == newNode->parent->parent->left) {
			uncle = newNode->parent->parent->right;
			// uncle is red
			if (uncle != nullptr && uncle->isBlack == false) {
				newNode->parent->isBlack = true;
				uncle->isBlack = true;
				newNode->parent->parent->isBlack = false;
				newNode = newNode->parent->parent;
			}
			else { // colour of uncle is black i.e. uncle is nullptr or black
				if (newNode == newNode->parent->right) {
					newNode = newNode->parent;
					leftRotation(newNode);
				}
				newNode->parent->isBlack = true;
				newNode->parent->parent->isBlack = false;
				rightRotation(newNode->parent->parent);
			}
		}
		else {
			// symmetric of if
			// parent is the right child of grandparent
			uncle = newNode->parent->parent->left;
			if (uncle != nullptr && uncle->isBlack == false ) {
				newNode->parent->isBlack = true;
				uncle->isBlack = true;
				newNode->parent->parent->isBlack = false;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == newNode->parent->left) {
					newNode = newNode->parent;
					rightRotation(newNode);
				}
				newNode->parent->isBlack = true;
				newNode->parent->parent->isBlack = false;
				leftRotation(newNode->parent->parent);
			}
		}
	}
	// Red Black Tree property
	root->isBlack = true;
	return true;
}

//The same algorithm disscussed in the class presentation
void RedBlackTree::leftRotation(NodeT* x)
{	
	NodeT* y = x->right;
	x->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {//x is the root
		root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

// symmetric to leftRotation function
void RedBlackTree::rightRotation(NodeT* x)
{
	NodeT* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	}
	else if (x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

bool RedBlackTree::remove(int key) {
	// nd is the potential node that contains the key to be removed 
	NodeT* nd = findNode(key);
	// key doesn't exit in the tree
	if (nd == nullptr) {
		return false;
	}
	// key found
	else {
		NodeT* y;
		NodeT* x;
		NodeT* xp; // x's parent
		bool LoR = NULL; // boolean check if the nodes is left or right child of its parent
		// nd has one or no children
		if (nd->left == nullptr || nd->right == nullptr) {
			y = nd; //node to be removed		
		}
		// nd has two children
		else {
			y = getPredecessor(nd); // y is the predecessor of nd
		}
		// check if y's only child is right or left
		if (y->left != nullptr) {
			x = y->left;
			xp = y;
			}
		else {
			x = y->right;
			xp = y;
		}
		// detach x from y (if x is not nullptr)
		if (x != nullptr) {
			x->parent = y->parent;
			xp = x->parent;
		}
		else {
			xp = y->parent;
		}
		if (y->parent == nullptr) {// y is the root
			root = x;
		}
		else {
			// attach x to y's parent
			if (y == y->parent->left) { // y is a left child
				y->parent->left = x;
				xp = y->parent;
			}
			else {
				y->parent->right = x;
				xp = y->parent;
			}
		}
		// check if x's parent(the note got move) is a left or right child
		if (xp->parent) {
			LoR = leftOrRight(xp);
		}
		// y has been moved up
		if (y != nd) {
			// replace nd with y
			nd->key = y->key;
			nd->value = y->value;
		}
		if (y->isBlack == true) {
			fixTree(x, xp, LoR);
		}	
		return true;
	}
}

//helper function for the node to be remove
NodeT* RedBlackTree::findNode (int key) const {
	// p is the potential node that contains the key to be removed 
	NodeT* p = root;
	while (p != nullptr) {
		if (key == p->key) {
			// key found, return the node that's to be removed
			return p;
		}
		if (key < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	return p;
}

//find predecessor of the parameter 
NodeT* RedBlackTree::getPredecessor(NodeT* nd) const {
	NodeT* p = nd->left;
	while (p->right != nullptr) {
		p = p->right;
	}
	return p;
}

bool RedBlackTree::leftOrRight(NodeT* p) {
	if (p = p->parent->left) {
		return true;
	}
	else {
		return false;
	}
}

//helper function fix the violation of red black tree
void RedBlackTree::fixTree(NodeT* x, NodeT* xp , bool LoR) {
	while (x != root && (x == nullptr || (x != nullptr && x->isBlack == true ))) {
		if (x == xp->left) //x is left child
		{
			NodeT* y = xp->right; //x's sibling
			if (y != nullptr && y->isBlack == false) {
				y->isBlack = true;
				xp->isBlack = false; //x's parent must have been black since y is red
				leftRotation(xp);
				y = xp->right;
			}
			if (y->left != nullptr && y->left->isBlack == true && y->right != nullptr && y->right->isBlack == true) {
				y->isBlack = false;
				x = xp;
			}
			else {
				if (y->right != nullptr && y->right->isBlack == true) {
					y->left->isBlack = true;
					y->isBlack = false;
					rightRotation(y);
					y = xp->right;
				}
				y->isBlack = xp->isBlack;
				xp->isBlack = true;
				if (y->right != nullptr) {
					y->right->isBlack = true;
				}
				leftRotation(xp);
				x = root;			
			}	
		}
		else 
		// symmetric to if
		{
			NodeT* y = xp->left; 
			if (y->isBlack == false) {
				y->isBlack = true;
				xp->isBlack = false; 
				rightRotation(xp);
				y = xp->left;
			}
			if (y->right != nullptr && y->right->isBlack == true && y->left != nullptr && y->left->isBlack == true) {
				y->isBlack = false;
				x = xp;
			}
			else {
				if (y->left !=nullptr && y->left->isBlack == true) {
					y->right->isBlack = true;
					y->isBlack = false;
					rightRotation(y);
					y = x->parent->left;
				}
				y->isBlack = xp->isBlack;
				xp->isBlack = true;
				if (y->left != nullptr) {
					y->left->isBlack = true;
				}
				rightRotation(xp);
				x = root;
			}		
		}
	}
	x -> isBlack = true;
}

bool RedBlackTree::search(int key) {
	NodeT* p = root;
	while (p != nullptr) {
		if (key == p->key) {
			return true;	
		}
		else if (key < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	return false;
}

vector<char> RedBlackTree::search(int key1, int key2) const {
	vector<char> v;
	searchHelper(root, v, key1, key2);
	return v;
}

// in-order traversal helper function to insert the value into the vector
void RedBlackTree::searchHelper(NodeT* nd, vector<char>& v, int key1, int key2) const {
	if (nd != nullptr) {
		// if key1 is smaller than nd->key, search the leftside of nd
		if (key1 < nd->key) {
			searchHelper(nd->left, v, key1, key2);
		}
		// if nd->key is within the range of key1 and key 2, insert the value into the vector
		if (key1 <= nd->key && key2 >= nd -> key) {
			v.push_back(nd -> value);
		}
		// if key2 is larger than nd->key, search the rightside of nd
		if (key2 > nd->key) {
			searchHelper(nd->right, v, key1, key2);
		}
	}
}

vector<char> RedBlackTree::values() const {
	vector<char> v;
	valueHelper(root, v);
	return v;
}

// in-order traversal to insert the values into the vector
void RedBlackTree::valueHelper(NodeT* nd, vector<char>& v) const {
	if (nd != nullptr) {
		valueHelper(nd->left, v);
		v.push_back(nd->value);
		valueHelper(nd->right, v);
	}
}

vector<int> RedBlackTree::keys() const {
	vector<int> v;
	keyHelper (root, v);
	return v;
}

// in-order traversal to insert the keys into the vector
void RedBlackTree::keyHelper(NodeT* nd, vector<int>& v) const {
	if (nd != nullptr) {
		keyHelper(nd->left, v);
		v.push_back(nd->key);
		keyHelper(nd->right, v);
	}
}

int RedBlackTree::size() {
	return sizeHelper(root);
}

// recursive helper function to get the size of the tree
int RedBlackTree::sizeHelper(NodeT* nd) {
	// base case
	if (nd == nullptr) {
		return 0;
	}
	else{
		count = 1 + sizeHelper(nd->left) + sizeHelper(nd->right);
	}
	return count;
}

NodeT* RedBlackTree::getRoot() const {
	return root;
}

void RedBlackTree::print() const
{
	inOrderPrint(root);
	cout << endl;
}

void RedBlackTree ::inOrderPrint(NodeT* nd) const
{
	if (nd != nullptr) {
		inOrderPrint(nd->left);
		cout << nd->value << " ";
		inOrderPrint(nd->right);
	}
}


int RedBlackTree::height() const
{
	return height(root);
}

// Helper method for height() if desired
int RedBlackTree::height(NodeT* nd) const
{
	// base case if the root of that tree or subtree is empty
	if (nd == nullptr) {
		return -1;
	}

	int leftHeight, rightHeight;

	// the height of a node nd is the length of the longest path from nd to a leaf
	leftHeight = height(nd->left);
	rightHeight = height(nd->right);

	// find the longest path, increment its number by 1 to get the height of the parent node of tha subtree
	if (leftHeight >= rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}
}