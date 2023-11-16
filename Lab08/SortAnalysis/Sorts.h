/* Kyle Tranfaglia
 * COSC320 - Lab07 - Ex.1
 * 11/03/2023
 * Sorting algorithms - Provided by Dr. Spickler - Bucket Sort updated to accept # of buckets as parameter
*/
#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

template<class T> bool sorted(T A[], int size);

template<class T> void bubble(T A[], int size);
template<class T> void insertion(T A[], int size);
template<class T> void selection(T A[], int size);
template<class T> void merge(T A[], T Temp[], int startA, int startB, int end);
template<class T> void mergeSort(T A[], T Temp[], int start, int end);
template<class T> void mergeSort(T A[], int size);
template<class T> void quickSort(T A[], int left, int right);
template<class T> void quickSort(T A[], int size);
template<class T> void combsort(T data[], const int n);
template<class T> void Shellsort(T data[], int n);
template<class T> void moveDown(T data[], int first, int last);
template<class T> void heapsort(T data[], const int n);
template<class T> void radixsort(T data[], const int n, const int radix);
template<class T> void countsort(T *A, long sz); // T needs to be an integer type.
template<class T> void BucketSort(T *A, long sz, long buckets); // T needs to be an float type.

//  Implementations

//  Support function to test sorting.

template<class T>
bool sorted(T A[], int size) {
	for (int i = 0; i < size - 1; i++)
		if (A[i] > A[i + 1])
			return false;

	return true;
}

// Bubble, Insertion, and Selection Sorts

template<class T>
void bubble(T A[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (A[j] > A[j + 1]) {
				T temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
}

template<class T>
void insertion(T A[], int size) {
	for (int i = 0; i < size; i++) {
		int j = 0;
		T val = A[i];
		for (j = i; j > 0 && A[j - 1] > val; j--)
			A[j] = A[j - 1];

		A[j] = val;
	}
}

template<class T>
void selection(T A[], int size) {
	int minindex;

	for (int i = 0; i < size; i++) {
		minindex = i;
		for (int j = i; j < size; j++)
			if (A[j] < A[minindex])
				minindex = j;

		T val = A[i];
		A[i] = A[minindex];
		A[minindex] = val;
	}
}

///////////////////////////////////////////////////////////
//  Merge Sort
///////////////////////////////////////////////////////////

template<class T>
void merge(T A[], T Temp[], int startA, int startB, int end) {
	int aptr = startA;
	int bptr = startB;
	int i = startA;

	while (aptr < startB && bptr <= end)
		if (A[aptr] < A[bptr])
			Temp[i++] = A[aptr++];
		else
			Temp[i++] = A[bptr++];

	while (aptr < startB)
		Temp[i++] = A[aptr++];

	while (bptr <= end)
		Temp[i++] = A[bptr++];

	for (i = startA; i <= end; i++)
		A[i] = Temp[i];
}

template<class T>
void mergeSort(T A[], T Temp[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		mergeSort(A, Temp, start, mid);
		mergeSort(A, Temp, mid + 1, end);
		merge(A, Temp, start, mid + 1, end);
	}
}

template<class T>
void mergeSort(T A[], int size) {
	T *Temp = new T[size];
	mergeSort(A, Temp, 0, size - 1);
	delete[] Temp;
}

///////////////////////////////////////////////////////////
//  Quick Sort
///////////////////////////////////////////////////////////

template<class T>
void quickSort(T A[], int left, int right) {
	int i = left;
	int j = right;
	int mid = (left + right) / 2;

	T pivot = A[mid];

	while (i <= j) {
		while (A[i] < pivot)
			i++;

		while (A[j] > pivot)
			j--;

		if (i <= j) {
			T tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			i++;
			j--;
		}
	}

	if (left < j)
		quickSort(A, left, j);

	if (i < right)
		quickSort(A, i, right);
}

template<class T>
void quickSort(T A[], int size) {
	quickSort(A, 0, size - 1);
}

///////////////////////////////////////////////////////////
//  Comb Sort
///////////////////////////////////////////////////////////

template<class T>
void combsort(T data[], const int n) {
	int step = n, j, k;
	// phase 1
	while ((step = int(step / 1.3)) > 1)
		for (j = n - 1; j >= step; j--) {
			k = j - step;
			if (data[j] < data[k])
				swap(data[j], data[k]);
		}

	// phase 2
	bool again = true;
	for (int i = 0; i < n - 1 && again; i++)
		for (j = n - 1, again = false; j > i; --j)
			if (data[j] < data[j - 1]) {
				swap(data[j], data[j - 1]);
				again = true;
			}
}

///////////////////////////////////////////////////////////
//  Shell Sort
///////////////////////////////////////////////////////////

template<class T>
void Shellsort(T data[], int n) {
	int i, j, hCnt, h;
	int increments[20], k;
// create an appropriate number of increments h
	for (h = 1, i = 0; h < n; i++) {
		increments[i] = h;
		h = 3 * h + 1;
	}
// loop on the number of different increments h
	for (i--; i >= 0; i--) {
		h = increments[i];
// loop on the number of subarrays h-sorted in ith pass
		for (hCnt = h; hCnt < 2 * h; hCnt++) {
// insertion sort for subarray containing every hth element of
			for (j = hCnt; j < n;) { // array data
				T tmp = data[j];
				k = j;
				while (k - h >= 0 && tmp < data[k - h]) {
					data[k] = data[k - h];
					k -= h;
				}
				data[k] = tmp;
				j += h;
			}
		}
	}
}

///////////////////////////////////////////////////////////
//  Heap Sort
///////////////////////////////////////////////////////////

template<class T>
void moveDown(T data[], int first, int last) {
	int largest = 2 * first + 1;
	while (largest <= last) {
		if (largest < last && // first has two children (at 2*first+1 and
				data[largest] < data[largest + 1]) // 2*first+2) and the second
			largest++;                      // is larger than the first;

		if (data[first] < data[largest]) {   // if necessary,
			swap(data[first], data[largest]);   // swap child and parent,
			first = largest;                // and move down;
			largest = 2 * first + 1;
		} else
			largest = last + 1;  // to exit the loop: the heap property
	}                           // isn't violated by data[first];
}

template<class T>
void heapsort(T data[], const int n) {
	int i;
	for (i = n / 2 - 1; i >= 0; --i) // create the heap;
		moveDown(data, i, n - 1);
	for (i = n - 1; i >= 1; --i) {
		swap(data[0], data[i]);     // move the largest item to data[i];
		moveDown(data, 0, i - 1);      // restore the heap property;
	}
}

///////////////////////////////////////////////////////////
//  Radix Sort: implementation for integer data.
///////////////////////////////////////////////////////////

template<class T>
void radixsort(T data[], const int n, const int radix) {
	T d, j, k, factor;
	T max = data[0];
	for (int i = 0; i < n; i++)
		if (max < data[i])
			max = data[i];

	deque<T> queues[radix];
	for (d = 0, factor = 1; max / factor > 0; factor *= radix, d++) {
		for (j = 0; j < n; j++)
			queues[(data[j] / factor) % radix].push_back(data[j]);
		for (j = k = 0; j < radix; j++)
			while (!queues[j].empty()) {
				data[k++] = queues[j].front();
				queues[j].pop_front();
			}
	}
}

///////////////////////////////////////////////////////////
//  Count Sort: implementation for positive integer data.
///////////////////////////////////////////////////////////

template<class T>
void countsort(T *A, long sz) {
	T maxval = A[0];
	for (int i = 0; i < sz; i++)
		maxval = max(maxval, A[i]);

	int *counts = new int[maxval + 1]();
	int *temp = new int[sz];

	for (int i = 0; i < sz; i++)
		counts[A[i]]++;

	for (int i = 1; i < maxval + 1; i++)
		counts[i] += counts[i - 1];

	for (int i = 0; i < sz; i++)
		temp[--counts[A[i]]] = A[i];

	copy(temp, temp + sz, A);
	delete[] temp;
	delete[] counts;
}

///////////////////////////////////////////////////////////
//  Bucket Sort: implementation for floating point data in [0, 1).
///////////////////////////////////////////////////////////

template<class T>
void BucketSort(T *A, long sz, long buckets) {
//	deque<T> *Buckets = new deque<T> [sz];
	vector<T> *Buckets = new vector<T> [buckets];

	for (long i = 0; i < sz; i++)
		Buckets[static_cast<long>(buckets * A[i])].push_back(A[i]);

//	for (long i = 0; i < sz; i++)
//		sort(Buckets[i].begin(), Buckets[i].end());

	for (long i = 0; i < buckets; i++)
		insertion(Buckets[i].data(), Buckets[i].size());

	int pos = 0;
	for (long i = 0; i < buckets; i++)
		for (long j = 0; j < Buckets[i].size(); j++)
			A[pos++] = Buckets[i][j];

	delete[] Buckets;
}

#endif /* SORTS_H_ */
