/*
* lab10.cpp
*
* Implementations of binary search, Fisher-Yates shuffling, and insertion
* sort (with added timing code) for analysis practice.  There are also some
* convenience methods to provide vectors of integers to use in testing.
*
* Author: C. Painter-Wakefield
*
* Last modified: 11/3/2016
*/

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace std;

/* Function prototypes */
/* Algorithms */
double binary_search(const vector<int> &vec, int search_val);
int    binary_search(const vector<int> &vec, int search_val, int left, int right);
double insertion_sort(vector<int> &vec);
double shuffle(vector<int> &vec);

/* Utility */
vector<int> range_vector(int size);
vector<int> random_vector(int size);


/* main() */
int main() {

	// each of the algorithm functions provided returns the time taken
	// in running the algorithm.

	// set out constants for N for each method.
	// note, set to 0 if you do not want to run a method
	const int N_SHUFFLE = 0;// range of 1000 to 500000 seems to work
	const int N_INSERT = 0;	// a range of 100 to 3000 seems to work
	const int N_BSEARCH = 125000;   // a range of 1000 to 500000 seems to work

	double t1 = 0;
	double t2 = 0;
	double t3 = 0;

	// Better timing data can be obtained by averaging many trial runs
	// of the same algorithm.  This can even out differences due to 
	// various types of interference, or differences in the data input.
	// This is generally called a monte carlo analysis
	const int MONTECARLO_TRIES = 100;

	// test shuffle
	if (N_SHUFFLE) {
		vector<int> vec;
		for (int i = 0; i < MONTECARLO_TRIES; i++) {
			vec = range_vector(N_SHUFFLE);  // this builds us a test vector
			t1 += shuffle(vec);
		}
		cout << "Shuffled " << N_SHUFFLE << " elements in " << t1 / MONTECARLO_TRIES << " seconds (average)." << endl;
		cout << "Total time: " << t1 << " seconds." << endl;
	}

	// test insertion_sort
	if (N_INSERT) {
		vector<int> vec;
		for (int i = 0; i < MONTECARLO_TRIES; i++) {
			vec = random_vector(N_INSERT); // this builds us a test vector
			t2 += insertion_sort(vec);
		}
		cout << "Sorted " << N_INSERT << " elements in " << t2 / MONTECARLO_TRIES << " seconds (average)." << endl;
		cout << "Total time: " << t2 << " seconds." << endl;
	}

	if (N_BSEARCH) {
		vector<int> vec;
		for (int i = 0; i < MONTECARLO_TRIES; i++) {
			vec = range_vector(N_BSEARCH); // input to binary search *must* be ordered
			t3 += binary_search(vec, rand() % vec.size());
		}
		cout << "Searches " << N_BSEARCH << " elements in " << t3 / MONTECARLO_TRIES << " seconds (average)." << endl;
		cout << "Total time: " << t3 << " seconds." << endl;
	}

	cin.get();
}

/*
* double shuffle(vector<int> &vec)
* Fisher-Yates shuffle
* Shuffles a vector of integers in place.  Returns the processor time taken, in
* seconds.  The algorithm used is the Fisher-Yates algorithm.
*/
double shuffle(vector<int> &vec) {
	clock_t start = clock();

	int i = vec.size() - 1;

	// note, this could be a for loop but implemented this way 
	// to match the pseudocode
	while (i > 0) {
		int index = rand() % (i + 1);
		swap(vec[index], vec[i]);
		i--;
	}

	clock_t stop = clock();
	return (stop - start) / double(CLOCKS_PER_SEC);
}



/*
* double insertion_sort(vector<int> &vec)
* Sorts a vector of integers in place.  Returns the processor time taken, in
* seconds.
*/
double insertion_sort(vector<int> &vec) {
	clock_t start = clock();

	for (int i = 1; i < (int)vec.size(); i++) {
		int x = vec[i];
		int j = i - 1;
		while (j >= 0 && vec[j] > x) {
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = x;
	}

	clock_t stop = clock();
	return (stop - start) / double(CLOCKS_PER_SEC);
}

/*
double binary_search(const vector<int> &vec, int search_val)
Takes in an *already sorted* vector of integers, and searches the vector for
the search value.  When the value is found, or is determined not to be in
the vector, the function returns.  (Normally, this function would return the
index of the found value, but this code returns a double reflecting the
number of seconds spent in the algorithm, instead.)
*/
double binary_search(const vector<int> &vec, int search_val) {
	clock_t start = clock();

	int ans = binary_search(vec, search_val, 0, vec.size() - 1);

	clock_t stop = clock();
	return (stop - start) / double(CLOCKS_PER_SEC);
}

/*
* int binary_search(const vector<int> &vec, int search_val, int left, int right)
* The actual recursive implementation of the binary search algorithm.  In
* addition to the vector and the search value, this function takes in the
* left hand and right hand indices bounding the part of the vector being
* searched.  The function returns the index of the found value, or -1 if not
* found.
*/
int binary_search(const vector<int> &vec, int search_val, int left, int right) {
	// search runs too fast, so this first code is just to slow things down...
	for (int i = 0; i < 100000; i++) {
		int j = 2 * i;
	}

	if (left > right) {
		return -1;
	}
	int pivot = left + (right - left) / 2;

	if (vec[pivot] == search_val) {
		return pivot;
	}
	else if (search_val < vec[pivot]) {
		return binary_search(vec, search_val, left, pivot - 1);
	}
	else {
		return binary_search(vec, search_val, pivot + 1, right);
	}
}

/*
* vector<int> range_vector(int size)
* Return a vector<int> containing all the integers from 0 to size - 1, in
* order.
*/
vector<int> range_vector(int size) {
	vector<int> answer(size);

	for (int i = 0; i < size; i++) {
		answer[i] = i;
	}
	return answer;
}

/*
* vector<int> random_vector(int size)
* Return a vector<int> containing random integers, in no particular order.
*/
vector<int> random_vector(int size) {
	vector<int> answer(size);
	for (int i = 0; i < size; i++) {
		answer[i] = rand();
	}
	return answer;
}
