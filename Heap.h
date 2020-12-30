#pragma once
#include<stdexcept>
#include<vector>
using std::vector;
using std::runtime_error;

template <class T>
class Heap
{
public:
	Heap(int n);
	Heap(const Heap& hp);
	Heap& operator=(const Heap& hp);
	~Heap();

	void insert(T x);
	T remove();
	T peek() const;
	Heap merge(const Heap& hp);
	int size() const;

private:
	T* arr;
	// Record the maximum size of the Heap
	int maxSize;
	// Record the current size of the Heap
	int currentSize;

	// helper method for copy constructor and overloaded assignment operator=
	void copyHeap(const Heap& hp);

	void bubbleUp(int i);
	void bubbleDown(int i);
};

// Returns the m smallest values in the vector
// PRE: m must be non-negarive
template <class T>
vector<T> smallestm(vector<T> v, int m) {
	// Note: the Heap remove function always removes the largest element in the current Heap
	int n = v.size();
	if (m > n) {
		Heap<T> hp(n);
		vector<T> t(n);
		// Insert all the elements of the vector into a heap
		for (int i = 0; i < n; i++) {
			hp.insert(v[i]);
		}
		// Remove all the root of the current heap and insert them into a vector
		// Insertion in reverse order, so the values in vector are in ascending order
		for (int i = n; i > 0; i--) {
			t[i - 1] = hp.remove();
		}
		return t;
	}
	// Case where m <= n and m != 0
	else if (m != 0) {
		Heap<T> hp(m);
		vector<T> t(m);
		// Insert the first m elements of the vector into a heap
		for (int i = 0; i < m; i++) {
			hp.insert(v[i]);
		}
		// For the remaining elements of the vector, if the current element is smaller than the root of the heap
		for (int i = m; i < n; i++) {
			if (v[i] < hp.peek()) {
				// Remove the root(the largest element), then the insert the element from the vector
				hp.remove();
				hp.insert(v[i]);
			}
		}
		for (int i = m; i > 0; i--) {
			t[i - 1] = hp.remove();
		}
		return t;
	}
	else {
		vector<T> t(m);
		return t;
	}
}

// Heap method implementations
// Constructor, parameter n is the max size of the heap's underlying array
template <class T>
Heap<T>::Heap(int n) {
	maxSize = n;
	currentSize = 0;
	arr = new T[maxSize];
}

// Copy constructor
template <class T>
Heap<T>::Heap(const Heap& hp) {
	copyHeap(hp);
}

template <class T>
Heap<T>& Heap<T>::operator=(const Heap& hp) {
	if (this != &hp) {
		delete[] arr;
		copyHeap(hp);
	}
	return *this;
}

// Deep copy helper method
template <class T>
void Heap<T>::copyHeap(const Heap& hp) {
	maxSize = hp.maxSize;
	currentSize = hp.currentSize;
	// Copy the underlying array
	arr = new T[maxSize];
	for (int i = 0; i < currentSize; i++) {
		arr[i] = hp.arr[i];
	}
}

template <class T>
Heap<T>::~Heap() {
	delete[] arr;
	arr = nullptr;
}

// PARA: element to be inserted
template <class T>
void Heap<T>::insert(T x) {
	// Throw an error when Heap is full, i.e. current size of the Heap reaches the max size
	if (currentSize == maxSize) {
		throw runtime_error("Heap full");
	}
	else {
		// insert the element at the end of the Heap
		arr[currentSize] = x;
		bubbleUp(currentSize);
		currentSize++;
	}
}

template <class T>
T Heap<T>::remove() {
	// Throw an error if the Heap is empty
	if (currentSize == 0) {
		throw runtime_error("Heap empty");
	}
	else {
		T removed = arr[0];
		// Replace the root with the right-most leaf
		arr[0] = arr[currentSize - 1];
		currentSize--;
		// Bubbledown the root
		bubbleDown(0);
		return removed;
	}
}

// The same function discussed in the lecture
template <class T>
void Heap<T>::bubbleUp(int i) {
	int parent = (i - 1) / 2;
	if (i > 0 && arr[i] > arr[parent]) {
		T temp = arr[i];
		arr[i] = arr[parent];
		arr[parent] = temp;
		bubbleUp(parent);
	}
}

template <class T>
void Heap<T>::bubbleDown(int i) {
	int parent = i;

	// left and right children of the parent
	int left = i * 2 + 1;
	int right = i * 2 + 2;

	// move the parent index down(for next recursion) if the child element is larger than the parent
	if (left < currentSize && arr[left] > arr[parent]) {
		parent = left;
	}
	if (right < currentSize && arr[right] > arr[parent]) {
		parent = right;
	}
	// swap the new parent (parent) and the old parent(i)
	if (parent != i) {
		T temp = arr[i];
		arr[i] = arr[parent];
		arr[parent] = temp;
		bubbleDown(parent);
	}
}

template <class T>
T Heap<T>::peek() const {
	// Throw an error when Heap is empty
	if (currentSize == 0) {
		throw runtime_error("Heap empty");
	}
	else {
		return arr[0];
	}
}

template <class T>
Heap<T> Heap<T>::merge(const Heap& hp) {
	// Create a Heap with size equals to the sum of the current sizes of the calling object and the parameter
	Heap merged(currentSize + hp.currentSize);
	// Insert the calling object into the Heap
	for (int i = 0; i < currentSize; i++) {
		merged.insert(arr[i]);
	}
	// Insert the parameter into the Heap
	for (int i = 0; i < hp.currentSize; i++) {
		merged.insert(hp.arr[i]);
	}
	return merged;
}

// Returns the current size of the heap
template <class T>
int Heap<T>::size() const {
	return currentSize;
}
