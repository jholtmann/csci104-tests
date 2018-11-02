# csci104-tests
This repository contains my student-made test cases for University of Southern California's CSCI-104 "Data Structures and Object Oriented Design" class. Note that these test cases are not guaranteed to be comprehensive.

**Contributors:**  
- Jonathan Holtmann
- Matthew Treadwell
- Chase Zimmerman
- Chad Helou

Note that the test skeleton has been adapted from an example one provided by
the course staff. The libraries and most utilities in the testing_utils folders
have also been provided by course staff.

**Running the tests:**  
These tests are written using gtest, Google's C++ testing framework. Each homework folder contains either a Makefile or CMakeLists.txt file to compile and run the tests. For certain tests, I have also provided a jtest_hw*.py file that can automatically pull new tests from this repo and place them in your development folder. The script can also update itself and run the tests (with or without gdb and valgrind). Note that this script is not available for every assignment, so make sure to manually git pull to get new tests for these.

Please make sure the Google C++ Testing Framework is installed on your machine.
