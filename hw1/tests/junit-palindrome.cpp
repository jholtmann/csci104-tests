/* UNIT TESTS */

#include <iostream>
#include "../palindrome.cpp"
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage: ./junit-test-palindrome [num]" << endl;
		return 0;
	}
	for (int i = 0; i < atoi(argv[1]); i++) {
		string s = to_string(i);
		stringstream ss(s);

		bool is_palindrome = equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
		if (helper(ss, s.size()) == is_palindrome) {
			cout << "OK: " << i << ", is palindrome: " << is_palindrome << endl;
		} else {
			cout << "FAILED!" << endl;
			cout << "Press enter to continue" << endl;
			getchar();
		}
	}

  return 0;
}
