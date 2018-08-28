/* UNIT TESTS */

#include <iostream>
#include <limits>
#include <stdlib.h>
#include <vector>
#include <string>
#include "../flexCharManager.h"

using namespace std;

/* http://www.cplusplus.com/forum/articles/7312/ */
void pause() {
	cerr << "Press ENTER to continue... " << flush;
  cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}

int main(int argc, char *argv[]) {
  flexCharManager mngr;
	char* p;
	vector<char*> pointers;

	const string _FAIL = "\033[31m[FAIL] \033[0m";
	const string _OK = "\033[32m[OK] \033[0m";
	const string _NOTE = "\033[35m[NOTE] \033[0m";
	const string _TEST = "\033[36m[TEST] \033[0m";

	// TEST MASS MEMORY ALLOCATION
	cerr << _TEST << "Testing mass memory allocation" << endl;
	char* po1;
	po1 = mngr.alloc_chars(3000);
	for (int c = 0; c < 3000; c++) {
		po1[c] = 'a';
	}

	char* po2;
	po2 = mngr.alloc_chars(3000);
	for (int c = 0; c < 3000; c++) {
		po2[c] = 'b';
	}

	char* po3;
	po3 = mngr.alloc_chars(3000);
	for (int c = 0; c < 3000; c++) {
		po3[c] = 'c';
	}

	int count = 0;
	for (int i = 0; i < 3000; i++) {
		if (po1[i] == 'a') {
			count++;
		}
	}

	if (count == 3000) {
		cerr << _OK << "Correctly allocated 3000 'a' characters" << endl;
	} else {
		cerr << _FAIL << "FAILED: Characters allocated incorrectly" << endl;
		pause();
	}

	count = 0;
	for (int i = 0; i < 3000; i++) {
		if (po2[i] == 'b') {
			count++;
		}
	}

	if (count == 3000) {
		cerr << _OK << "Correctly allocated 3000 'b' characters" << endl;
	} else {
		cerr << _FAIL << "FAILED: Characters allocated incorrectly" << endl;
		pause();
	}

	count = 0;
	for (int i = 0; i < 3000; i++) {
		if (po3[i] == 'c') {
			count++;
		}
	}

	if (count == 3000) {
		cerr << _OK << "Correctly allocated 3000 'c' characters" << endl;
	} else {
		cerr << _FAIL << "FAILED: Characters allocated incorrectly" << endl;
		pause();
	}
	cerr << endl;

	// Max out buffer
	cerr << _TEST << "Try allocating another 1000 chars" << endl;
	p = mngr.alloc_chars(1000);
	cerr << "[DONE]" << endl << endl;

	// Adding when not enough space
	cerr << _TEST << "Try allocating when buffer is full" << endl;
	char* tmp;
	for (int i = 0; i < 100; i++) {
		tmp = mngr.alloc_chars(i);
		pointers.push_back(tmp);
	}
	cerr << "[DONE]" << endl << endl;

	// Free null pointer
	cerr << _TEST << "Try freeing null pointer" << endl;
	for (char* c : pointers) {
		mngr.free_chars(c);
	}
	pointers.clear();
	cerr << "[DONE]" << endl << endl;

	// Free all allocated memory
	cerr << _TEST << "Free currently allocated memory" << endl;
	mngr.free_chars(po1);
	mngr.free_chars(po2);
	mngr.free_chars(po3);
	mngr.free_chars(p);
	cerr << "[DONE]" << endl << endl;

	// Make sure buffer is empty
	cerr << _TEST << "Check if buffer was emptied by allocating 10000 chars" << endl;
	p = mngr.alloc_chars(10000);
	if (p != NULL) {
		cerr << _OK << "Buffer successfully freed" << endl;
		mngr.free_chars(p);
	} else {
		cerr << _FAIL << "Failed to allocate 10000 chars" << endl;
		pause();
	}
	cerr << endl;

	// Check with user
	cerr << _NOTE << "This next test can easily take 30-60 minutes to run due to valgrind." << endl;

	char in = '0';
	while (true) {
		cerr << "Continue? [y/n]: ";
		cin >> in;
		cerr << endl;

		if (in == 'y' || in == 'n')
			break;

	}

	if (in == 'n')
		return 0;

	cerr << endl;

	// Create 10000 single char allocations
	cerr << _TEST << "Create 10000 single char allocations (if running with valgrind, this can take hours)" << endl;
	for (int i = 0; i < 10000; i++) {
		p = mngr.alloc_chars(1);
		*p = 'a';
		pointers.push_back(p);
		if (i % 50 == 0)
			cerr << "\t Created pointer: "<< i << endl;
	}
	cerr << "[DONE]" << endl << endl;

	// Check returned pointers (should be sequential)
	cerr << _TEST << "Check if returned pointers and values are correct" << endl;
	bool failed = false;
	for (int i = 0; i < pointers.size()-1; i++) {
		if (pointers[i]+1 != pointers[i+1]) {
			failed = true;
			break;
		}
	}
	if (!failed) {
		cerr << _OK << "returned pointers were OK" << endl;
	} else {
		cerr << _FAIL << "returned pointers were incorrect" << endl;
		pause();
	}

	// Check allocated values
	failed = false;
	for (char* c : pointers) {
		if (*c != 'a') {
			failed = true;
			break;
		}
	}
	if (!failed) {
		cerr << _OK << "returned values were OK" << endl;
	} else {
		cerr << _FAIL << "returned values were incorrect" << endl;
		pause();
	}
	cerr << endl;

	// Free 2000 pointers in the middle of the buffer
	cerr << _TEST << "Trying to free 2000 pointers in middle of buffer" << endl;
	for (int i = 0; i < 2000; i++) {
		mngr.free_chars(pointers[2999] + i);
	}
	cerr << "[DONE]" << endl << endl;

	// Allocate 2000 characters
	cerr << "Trying to allocate 2000 chars" << endl;
	p = mngr.alloc_chars(2000);
	pointers.push_back(p);
	if (p != NULL) {
		cerr << _OK << "returned valid pointer" << endl;
	} else {
		cerr << _FAIL << "null pointer returned" << endl;
		pause();
	}
	cerr << endl;

	// Writing to new 2000 char pointer
	cerr << _TEST << "Testing writing to new pointer" << endl;
	for (int i = 0; i < 2000; i++) {
		p[i] = 'b';
	}
	cerr << "[DONE]" << endl << endl;

	// Check integrity
	cerr << _TEST << "Check if all values in buffer are correct" << endl;
	failed = false;
	for (int i = 0; i < 10000; i++) {
		tmp = pointers.at(0) + i;
		if (i < 2999 || i >= 4999) {
			if (*tmp != 'a') {
				cerr << _NOTE << "Expecting char 'a', found " << *tmp << endl;
				failed = true;
				break;
			}
		} else {
			if (*tmp != 'b') {
				cerr << _NOTE << "Expecting char 'b', found " << *tmp << endl;
				failed = true;
				break;
			}
		}
		// cerr << *tmp;
	}
	cerr << endl;
	if (!failed) {
		cerr << _OK << "all values were as expected" << endl;
	} else {
		cerr << _FAIL << "found unexpected values in buffer" << endl;
		pause();
	}
	cerr << endl;

	// Free all pointers
	cerr << _TEST << "Free all allocated pointers" << endl;
	for (char* c : pointers) {
		mngr.free_chars(c);
	}
	cerr << "[DONE]" << endl << endl;

	/* MORE TESTS HERE? */

	// Tests complete
	cerr << _NOTE << "Tests complete. Make sure to run this with valgrind ";
	cerr << "to check for memory leaks as well." << endl;
	cerr << _NOTE << "If you can think of more tests to add, please either add them ";
	cerr << "yourself or suggest them on Piazza." << endl << endl;

	cerr << _NOTE << "Author: Jonathan Holtmann" << endl;
	cerr << _NOTE << "Have a nice day!" << endl;

  return 0;
}
