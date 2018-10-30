# HW2 Tests

These tests use the Google C++ Testing Framework, making them much more
useful for diagnosing bugs in your code.

## Running the tests:   

First, copy the hw2-check and jtest_hw2.py files to your hw2 folder. You can then
use the provided python script to run the instructor-provided and new test cases
at the same time.    

Before running the python script, please insatll gitpython via the following command:   
```
sudo pip3 install gitpython
```

The syntax for the python script is as follows:   
```
usage: jtest_hw2.py [-h] [-s] [-d] [-v] [--credits] [-a]
                    [-t {ssort,clist,duckduck}] [-p] [-nv] [-g] [-u] [-np]
                    [-nu] [-ns] [--gitdir GITDIR] [--testdir TESTDIR]

JTest Script - HW2

optional arguments:
  -h, --help            show this help message and exit
  -s, --suppress        Suppress status messages
  -d, --debug           Enable debug messages
  -v, --version         show program's version number and exit
  --credits             Print credits and exit

test arguments:
  -a, --all             Run all HW2 test cases
  -t {ssort,clist,duckduck}, --test {ssort,clist,duckduck}
                        Runs individual test case
  -p, --pull            Pull test repo only
  -nv, --novalgr        Don't run valgrind on tests
  -g, --gdb             Run gdb on test cases. Helpful for tracing segfaults.
                        Does not run valgrind
  -u, --uninstall       Remove jtest files and exit

advanced arguments:
  -np, --nopull         Don't pull repository
  -nu, --noupdate       Don't update tests
  -ns, --noself         Don't update self
  --gitdir GITDIR       Override git directory (relative path)
  --testdir TESTDIR     Override tests directory (relative path)
```
