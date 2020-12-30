#pragma once

// helper swap method
template <class T>
void swaphelper(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}

// algorithm learned in class
template <class T>
int insertionsort(T arr[], int n) {
	// barometer operation counter
	int count = 0;
	for (int i = 1; i < n; ++i) {
		T temp = arr[i];
		int pos = i;
		// shuffle up all sorted items > arr[i]
		while (pos > 0 && arr[pos - 1] > temp) {
			arr[pos] = arr[pos - 1];
			pos--;
		}
		count++;
		// inser the current item
		arr[pos] = temp;
	}
	return count;
}

template <class T>
int partition(T arr[], int low, int high, int& count)
{	
	// set i to the first element of the partition, j to the rightmost element other than the pivot
	int i = low;
	int j = high - 1;
	while (i < j) {
		// barometer operations counter
		count++;
		// compare if arr[i] is greather than the pivot
		if (arr[i] > arr[high]) {
			while (j > i) {
				// compare if arr[j] is smaller than the pivot
				if (arr[j] < arr[high]) {
					// when both conditions are met, swap arr[i] and arr[j]
					swaphelper(arr[i], arr[j]);
					// only swap once, so break out of the inner loop after swap
					break;
				}
				j--;
			}
		}
		i++;
	}

	// when arr[j] is greater than or equals to the pivot, swap it with the pivot so all the elements 
	// on the right side of the pivot are greater than or equals to the pivot
	if (arr[j] >= arr[high]) {
		swaphelper(arr[j], arr[high]);
		return j;
	}
	// when arr[j] is smaller than the pivot, swap the next element with the pivot so all the elements
	// on the left side of the pivot are smaller than the pivot
	else {
		swaphelper(arr[j + 1], arr[high]);
		return j+1;
	}
	
}

//helper method for quicksort
template <class T>
int qshelper(T arr[], int low, int high, int& count)
{
	if (low < high) {
		int pivot = partition(arr, low, high, count);
		qshelper(arr, low, pivot - 1, count);
		qshelper(arr, pivot + 1, high, count);
	}
	return count;
}

template <class T>
int quicksort(T a[], int n) {
	// barometer operation counter
	int count = 0;
	return qshelper(a, 0, n-1,count);
}

/* got help from this website for mergesort 

Author: From University of Michigan
Date: 2006
Availability: http://csg.sph.umich.edu/abecasis/class/2006/615.09.pdf 
*/
template <class T>
int merge(T arr[], int low, int mid, int high, int& count) {
	int i, j, k;
	// size of the two temporary arrays
	int l = mid - low + 1;
	int r = high - mid;

	// make 2 temporary arrays, split and assign the values from the original array into the 2 temporary arrays
	// left array copies elements from index low to mid, right array copies elements from index mid+1 to high
	T* left = new T[l];
	T* right = new T[r];
	for (i = 0; i < l; i++)
		left[i] = arr[low + i];
	for (j = 0; j < r; j++)
		right[j] = arr[mid + j + 1];

	i = 0;
	j = 0;
	k = low;

	// merge the value back to the array in accending order
	// both conditions have to be met in order to excute this loop
	while (i < l && j < r){	
		count++;
		if (left[i] <= right[j]){
			arr[k++] = left[i++];
		}
		else{
			arr[k++] = right[j++];
		}
	}

	// only one of the while loop will be excuted
	// assign the remaining unassigned value back to the array
	while (i < l){
		arr[k++] = left[i++];
	}
	while (j < r){
		arr[k++] = right[j++];
	}
	return count;
}

template <class T>
int mergesort(T arr[], int n)
{	
	// barometer operation counter
	int count = 0;
	int size, low, mid, high;

	// divide the size of the array by 2 each time then merge back
	// when merging,  first merge two array of size 1 , then two arrays of size 2, then 4, then 8, etc.
	for (size = 1; size <n; size += size)
	{
		// set the low, mid, high point of the arrays that to be used in merge function
		for (low = 0; low < n - 1; low += size*2)
		{	
			if (low + size - 1 < n - 1) {
				mid = low + size - 1;
			}
			else {
				mid = n - 1;
			}

			if (low + 2 * size - 1 < n - 1) {
				high = low + 2 * size - 1;
			}
			else {
				high = n - 1;
			}
			// merge two arrays
			merge(arr, low, mid, high, count);
		}
	}
	return count;
}


/* learned shellsort from this video 
Author: Yusuf Shakeel
Date: 2015
Availability: https://www.youtube.com/watch?v=SCBf7aqKQEY 
*/
template <class T>
int shellsort(T arr[], int n) {
	// barometer operation counter
	int count = 0;
	// initial gap size is half of the size of the array
	// half the size of the gap each time
	for(int gap = n/2; gap >0; gap = gap / 2){
		for (int i = gap; i < n; i++) {
			// this loop keeps comparing two values between the gap, and keep swaping them until the the value at index j+gap is not smaller than j
			for (int j = i; j >= gap; j = j - gap) {
				count++;
				if (arr[j] >= arr[j - gap])
					// immediately stop the loop when the value at index j is not smaller than j-ap
					break;
				else {
					// keep swaping loop when element at index j is greater than j-gap
					swaphelper(arr[j], arr[j - gap]);
				}
			}
		}
	}
	return count;
}