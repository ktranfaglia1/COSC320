/* Kyle Tranfaglia
 * COSC320 - Lab07 - Ex.1
 * 11/03/2023
 * Sorting algorithms driver code for timing - Provided by Dr. Spickler - Bucket Sort updated to accept # of buckets as parameter
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "Sorts.h"
#include "timer.h"

using namespace std;

template<class T> void print(T A[], int size);
template<class T> void outputSorted(T A[], int size);

int main() {
	long n = 0, k = 0;
	int mod = 100000;
	double start, finish;
	char printyn = 'n';

	srand(time(0));

	char yn = 'n';

	cout << "Do integer array sort (y/n): ";
	cin >> yn;

	if (yn == 'y') {
		cout << "Input the array size: ";
		cin >> n;

		cout << "Input the maximum element size (0 for RAND_MAX): ";
		cin >> mod;

		cout << "Print arrays (y/n): ";
		cin >> printyn;

		long *A = new long[n];

		if (mod <= 1)
			for (long i = 0; i < n; i++) {
				A[i] = rand();
			}
		else
			for (long i = 0; i < n; i++) {
				A[i] = rand() % mod;
			}

		if (printyn == 'y' || printyn == 'Y')
			print(A, n);

		GET_TIME(start);

//	mergeSort(A, n);
// 	quickSort(A, n);
//	combsort(A, n);
//	Shellsort(A, n);
//	heapsort(A, n);
radixsort(A, n, 10000);
//	countsort(A, n);
// 	sort(A, A + n);

		GET_TIME(finish);

		if (printyn == 'y' || printyn == 'Y')
			print(A, n);

		cout << "\nThe code to be timed took " << finish - start << " seconds."
				<< endl;

		outputSorted(A, n);
	}

////////////////////////////////////////////////

	cout << "\n\nDo double array sort (y/n): ";
	cin >> yn;
	// yn = 'y';

	if (yn == 'y') {

		cout << "Input the array size: ";
		cin >> n;

		cout << "Input a bucket size: ";
		cin >> k;

		double *B = new double[n];
		for (long i = 0; i < n; i++)
			B[i] = 1.0 * rand() / RAND_MAX;

		GET_TIME(start);

		//	mergeSort(B, n);
		//	quickSort(B, n);
		//	combsort(B, n);
		//	Shellsort(B, n);
		//	heapsort(B, n);
		//	radixsort(B, n, 10);
		//	sort(B, B + n);
		 BucketSort(B, n, k);

		GET_TIME(finish);

		cout << "\nThe code to be timed took " << finish - start << " seconds."
				<< endl;

		outputSorted(B, n);
	}

	return 0;
}

template<class T>
void print(T A[], int size) {
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}

template<class T>
void outputSorted(T A[], int size) {
	if (sorted(A, size))
		cout << "Sorted" << endl;
	else
		cout << "Not Sorted" << endl;
}