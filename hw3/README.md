# HW3 Tests

These test cases use the Google C++ Testing Framework.

##Running the tests:   
**Step 1: Install the test script**

$ cd /path/to/your/hw-yourid/hw3
$ wget https://raw.githubusercontent.com/jholtmann/csci104-tests/master/hw3/jtest_hw3.py
$ sudo pip3 install gitpython
If you already installed gitpython for the last test cases, you don't have to again.

**Step 2: Initialize the test script**
```
$ python3 jtest_hw3.py
```
The script will copy the hw3-check directory into your folder

**Step 2.5: Copy your parser executable into the hw3-check folder**

You will have to do this any time you change parser. You also have to do this any time I decide to push an update to the cmake system, as your executable in hw3-check will be erased. I suggest just copying the executable over every time before you run the tests.
```
$ cd hw-yourid/hw3
$ make parser
$ cp parser hw3-check/parser
```

**Step 3: Run the tests**

Individually:
```
$ python3 jtest_hw3.py -t stack
$ python3 jtest_hw3.py -t parser
```

or run them all:
```
$ python3 jtest_hw3.py -a
```
