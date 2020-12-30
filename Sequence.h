#pragma once
#include<cmath> //for sqrt function
#include<algorithm> //for STL sort function
#include<iostream>

class Sequence
{
public:
	Sequence();
	Sequence(const Sequence &sq);
	Sequence & operator=(const Sequence & sq);
	~Sequence();
	
	void insert(double x);
	void insert(double arr[], int n);
	
	int find(double x) const;
	int size() const;
	double sum() const ;
	double mean() const;
	double median() const;
	double stddev() const;
	
	Sequence concatenate(const Sequence & sq) const;

private:
	double* arr;
	//current size of the array
	int curSize;
	//maximum size of the array
	int maxSize;

	//To be implemented in copy constructor and overloaded assignment operator
	void copySequence(const Sequence& sq) ;
};

