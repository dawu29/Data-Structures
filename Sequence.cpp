#include "Sequence.h"

//Makes an empty array of size 2
Sequence::Sequence() {
	maxSize = 2;
	arr = new double[maxSize];
	curSize = 0;
}

//Makes a deep copy of sq
Sequence::Sequence(const Sequence & sq) {
	copySequence(sq);
}

Sequence & Sequence::operator=(const Sequence& sq) {
	if (this != &sq) 
	{
		delete[] arr;
		copySequence(sq);
	}	
	return *this;
}

void Sequence::copySequence(const Sequence& sq) {
	// Deep copy
	maxSize = sq.maxSize;
	curSize = sq.curSize;
	// Copy the underlying array
	arr = new double[maxSize];
	for (int i = 0; i < curSize; i++)
	{
		arr[i] = sq.arr[i];
	}	
}

Sequence::~Sequence() {
	delete[] arr;
	arr = nullptr;
}

// PARAM: values to be inserted
// POST:value is inserted at the top of the Sequence
void Sequence::insert(double x) {
	// Double the the maximum size of the array if current size exceeds the maximum size
	if (curSize == maxSize) 
	{	
		maxSize = curSize * 2;
		double* temp = new double[maxSize];
		for (int i = 0; i < curSize; i++) 
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
	arr[curSize] = x;
	curSize++;
}

// PARAM: values to be inserted and number of values 
// POST: values are inserted at the top of the Seqeuence
void Sequence::insert(double add[], int n) {
	//Increase the maximun size if more space is required
	if (curSize + n >= maxSize) 
	{	
		maxSize = curSize + n;
		double* temp = new double[curSize + n];		
		//copy the the contents of the calling object's array 
		for (int i = 0; i < curSize; i++) 
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
	//insert the values of the parameter on top of the array
	for (int i = 0; i < n; i++)
	{	
		arr[curSize] = add[i];
		curSize++;
	}
}

// returns the number of elements whose value is equal to the parameter
int Sequence::find(double x) const {
	int num = 0;
	for (int i = 0; i < curSize; i++) {
		if (arr[i] == x) num++;
	}
	return num;
}

// returns the current number of values
int Sequence::size() const {
	return curSize;
}

double Sequence::sum() const {
	double sum = 0;
	for (int i = 0; i < curSize; i++)
	{
		sum += arr[i];
	}
	return sum;
}

double Sequence::mean() const {
	if (curSize == 0)
	{
		return 0;
	}
	double mean = sum() / curSize;
	return mean;
}

double Sequence::median() const {
	//sort the array in increasing order using the STL sort function in <algorithm> 
	std::sort(arr, arr+curSize);
	double median;
	if (curSize == 0) 
	{
			return 0;
	}

	if (curSize % 2 == 0)
	{
		median = (arr[curSize / 2 - 1] + arr[curSize / 2]) / 2;
		return median;
	}

	else
	{
		median = arr[curSize / 2];
		return median;
	}
}

// PRE: sequence is not empty
double Sequence::stddev() const {	
	if (curSize == 0)
	{
		return 0;
	}
	double m = mean();
	double sumDifference = 0;
	for (int i = 0; i < curSize; i++) 
	{	
		//adds up the square of the difference of each term
		sumDifference += pow(arr[i]-m, 2);
	}
	double deviation = sqrt(sumDifference / curSize);
	return deviation;
}

Sequence Sequence::concatenate(const Sequence & sq) const {
	//create an Sequence object that copies the calling object
	Sequence copy = *this;
	//insert the values of the parameter on top of the copy
	copy.insert(sq.arr,sq.size());
	return copy;
}
