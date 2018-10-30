# HW1 Tests

This repository contains test files for the HW1. This was my first foray into
test-writing; as such, the test cases are not very well written. As all
operations are performed on the same memory manager, errors can pile up and be
very difficult to diagnose. While the tests provide a decent overall test
of the functionality of your memory manager, they will make debugging any errors
difficult. I recommend trying to recreate any errors you encounter in a new main
file and diagnose them there before re-running the tests.

## Running the tests:   

**Compile palindrome check:**

Before you do this, comment out your main function in palindrome.cpp. You need to uncomment it after the tests are done.

```
$ g++ -g -std=c++11 tests/junit-palindrome.cpp -o junit-palindrome
```

**Compiling simpleCharManager check:**

```
$ g++ -g -std=c++11 simpleCharManager.cpp tests/junit-simplechar.cpp -o junit-simplechar
```

**Compiling flexCharManager check:**

```
$ g++ -g -std=c++11 flexCharManager.cpp simpleCharManager.cpp tests/junit-flexchar.cpp -o junit-flexchar
```

**Then run each:**
```
$ ./junit-palindrome 5000   
$ ./junit-simplechar   
$ ./junit-flexchar   
```

**If your code passes, run each with valgrind as well:**
```
$ valgrind --leak-check=full --show-leak-kinds=all ./junit-palindrome 5000   
$ valgrind --leak-check=full --show-leak-kinds=all ./junit-simplechar   
$ valgrind --leak-check=full --show-leak-kinds=all ./junit-flexchar   
```
