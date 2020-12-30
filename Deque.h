#pragma once
#include<stdexcept>
#include<iostream>
using std::runtime_error;

template <class T>
class Node
{
public:
	T data;
	//pointer to the next node
	Node* next;
	//pointer to the previous node
	Node* prev;

	//constructors
	Node() : data(NULL), next(nullptr), prev(nullptr) { ; };
	Node(T val) : data(val), next(nullptr), prev(nullptr) { ; };
	Node(T val, Node* n1, Node* n2) : data(val), next(n1), prev(n2) { ; };
};

template <class T>
class Deque
{
public:
	// constructor
	Deque() {
		head = nullptr;
		tail = nullptr;
	};

	// deep copy constructor
	Deque(const Deque & dq) {
		copyDeque(dq);
	};

	// destructor
	~Deque() {
		deleteDeque();
	};

	Deque & operator=(const Deque & dq) {
		if (this != &dq)
		{
			deleteDeque();
			copyDeque(dq);
		}
		return *this;
	};

	// Mutators
	// Value is inserted at the front of Deque
	void insertFront(T val) {
		Node<T>* newNode = new Node<T>(val);
		// check if the list is empty
		if (head == nullptr) {
			// set the inserted node to head and tail
			head = newNode;
			tail = newNode;
		}

		// reassign head
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
	};

	// Value is inserted at the back of Deque
	void insertBack(T val) {
		Node<T>* newNode = new Node<T>(val);
		// check if the list is empty
		if (head == nullptr) {
			// set the inserted node to head and tail
			head = newNode;
			tail = newNode;
		}

		// reassign tail
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	};

	// Value is removed at the front of the Deque
	T removeFront() {
		// check if the list is empty
		if (head == nullptr) {
			throw runtime_error("Deque empty");
		}
		T front = head->data;

		// the node to be removed is the only node in the list
		if (head->next == nullptr)
		{
			head = nullptr;
			tail = nullptr;
			return front;
		}

		else
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
			return front;
		}
	};

	// Value is removed at the back of the Deque
	T removeBack() {
		//check if the list if empty
		if (tail == nullptr) {
			throw runtime_error("Deque empty");
		}
		T back = tail->data;
		// the node to be removed is the only node in the list
		if (tail->prev == nullptr) 
		{	
			head = nullptr;
			tail = nullptr;
			return back;
		}
		else 
		{	
			//tail->prev = nullptr;
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
			return back;
		}
	};

	// returns the value at the front of the Deque
	T peekFront() const{
		if (head == nullptr) {
			throw runtime_error("Deque empty");
		}
		else {
			T peek = head->data;
			return peek;
		}
	};

	// returns the value at the end of the Deque
	T peekBack() const{
		if (tail == nullptr) {
			throw runtime_error("Deque empty");
		}
		else {
			T peek = tail->data;
			return peek;
		}
	};

	//check if the Deque is empty
	bool empty() const{
		return head == nullptr;
	};

	//return the number of items sorted in the Deque
	int size() const{
		int count = 0;
		Node<T>* c = head;
		while (c != nullptr) {
			count++;
			c = c->next;
		}
		delete c;
		c = nullptr;
		return count;
	};

private:
	// pointer to the front of the Deque
	Node<T>* head;
	// pointer to the back of the Deque;
	Node<T>* tail;

	// deepcopy, helper method for copy constructor and overload operator
	void copyDeque(const Deque & dq) {
		// copy an empty list
		if (dq.head == nullptr) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			// copy the first node in the list 
			head = new Node<T>(dq.head->data);
			tail = head;
			Node<T>* temp = dq.head->next;
			// copy the rest of the list
			while (temp != nullptr)
			{
				tail->next = new Node<T>(temp->data);
				tail->next->prev = tail;
				tail = tail->next;
				temp = temp->next;
			}
		}
	};

	// helper method for destructor
	void deleteDeque() {
		Node<T>* p = head;
		while (p != nullptr)
		{
			head = head->next;
			delete p;
			p = head;
		}
	};
};


