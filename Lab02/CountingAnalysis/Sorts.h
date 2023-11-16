/* Kyle Tranfaglia
*  COSC320 - Lab02 - Ex.1
*  Last updated 09/06/23
*  Declaration and Implimentation file for sorting alrgorithms - code provided by Dr. Spickler - modified to add counts
*/

///////////////////////////////////////////////////////////
// Sorting Algorithms
///////////////////////////////////////////////////////////

template<class T>
long bubble(T A[], int size) {
	long count = 3;
	for (int i = 0; i < size - 1; i++) {
		count += 3;
		for (int j = 0; j < size - i - 1; j++) {
			count += 6;
			if (A[j] > A[j + 1]) {
				T temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
				count += 5;
			}
		}
		count += 4;
	}
	return count;
}

///////////////////////////////////////////////////////////

template<class T>
long insertion(T A[], int size) {
	long count = 2;
	for (int i = 0; i < size; i++) {
		int j = 0;
		T val = A[i];
		for (j = i; j > 0 && A[j - 1] > val; j--) {
			A[j] = A[j - 1];
			count +=2;
		}

		A[j] = val;
		count += 9;
	}
	return count;
}

///////////////////////////////////////////////////////////

template<class T>
long selection(T A[], int size) {
	long count = 2;
	int minindex;

	for (int i = 0; i < size; i++) {
		minindex = i;
		for (int j = i; j < size; j++) {
			count += 3;
			if (A[j] < A[minindex]) {
				minindex = j;
				count++;
			}
		}
		T val = A[i];
		A[i] = A[minindex];
		A[minindex] = val;
		count += 8;
	}
	return count;
}

///////////////////////////////////////////////////////////

template<class T>
long merge(T A[], T Temp[], int startA, int startB, int end) {
	long count = 3;
	int aptr = startA;
	int bptr = startB;
	int i = startA;

	while (aptr < startB && bptr <= end) {
		if (A[aptr] < A[bptr])
			Temp[i++] = A[aptr++];
		else
			Temp[i++] = A[bptr++];

		count += 6;
	}

	while (aptr < startB) {
		Temp[i++] = A[aptr++];
		count += 4;
	}

	while (bptr <= end) {
		Temp[i++] = A[bptr++];
		count += 4;
	}

	for (i = startA; i <= end; i++) {
		A[i] = Temp[i];
		count += 3;
	}
	count += 6;
	
	return count;
}

template<class T>
long mergeSort(T A[], T Temp[], int start, int end) {
	long count = 0;
	if (start < end) {
		int mid = (start + end) / 2;
		count += mergeSort(A, Temp, start, mid);
		count += mergeSort(A, Temp, mid + 1, end);
		count += 5;
		count += merge(A, Temp, start, mid + 1, end);
	}
	count++;

	return count;
}

template<class T>
long mergeSort(T A[], int size) {
	long count = 1;
	T *Temp = new T[size];
	count += mergeSort(A, Temp, 0, size - 1);
    delete [] Temp;

	return count;
}

///////////////////////////////////////////////////////////

template<class T>
long quickSort(T A[], int left, int right) {
	long count = 6;
	int i = left;
	int j = right;
	int mid = (left + right) / 2;

	T pivot = A[mid];

	while (i <= j) {
		while (A[i] < pivot) {
			i++;
			count += 2;
		}

		while (A[j] > pivot) {
			j--;
			count += 2;
		}

		if (i <= j) {
			T tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			i++;
			j--;
			count += 5;
		}
		count += 4;
	}

	if (left < j)
		count += quickSort(A, left, j);

	if (i < right)
		count += quickSort(A, i, right);

	count += 3;

	return count;
}

template<class T>
long quickSort(T A[], int size) {
	long count = 1;
	count += quickSort(A, 0, size - 1);

	return count;
}