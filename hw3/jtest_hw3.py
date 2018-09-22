#!/usr/bin/python3

import subprocess
import string
import git
import sys
import os
import argparse
import shutil
import hashlib

#####################################################
# AUTHOR: Jonathan Holtmann
# CSCI 104 HW3 Test Case Script
#####################################################

repo_url = "https://github.com/jholtmann/csci104-tests"
script_dir = os.path.dirname(os.path.realpath(__file__))
script_path = os.path.realpath(__file__)
version = "v2.24"

class bcolors:
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKGREEN = '\033[92m'
	WARNING = '\033[93m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'

def print_banner(str):
	print("########################################################")
	print("                     %s                  " % str)
	print("########################################################")

def print_credits():
	print('JTest HW3 ' + version)
	print("Author: Jonathan Holtmann")
	print("Tests by: Jonathan Holtmann, Matthew Treadwell")

# https://www.pythoncentral.io/how-to-recursively-copy-a-directory-folder-in-python/
def copyDirectory(src, dest):
    try:
        shutil.copytree(src, dest)
    # Directories are the same
    except shutil.Error as e:
        print('Directory not copied. Error: %s' % e)
    # Any error saying that the directory doesn't exist
    except OSError as e:
        print('Directory not copied. Error: %s' % e)

def git_pull(gdir):
	try:
		if not suppress: print("jtest: Pulling repo %s" % gdir)
		repo = git.Repo(gdir)
		hash = repo.head.object.hexsha
		o = repo.remotes.origin
		o.pull(o.refs[0].remote_head)

		if repo.head.object.hexsha != hash:
			return True
		else:
			return False
	except git.exc.GitCommandError:
		print("jtest: Failed to pull git repository")
		sys.exit()

def git_clone(gdir):
	try:
		if not suppress: print("jtest: Cloning %s into %s" % (repo_url, gdir))
		repo = git.Repo.init(gdir)
		origin = repo.create_remote('origin', repo_url)
		origin.fetch()
		origin.pull(origin.refs[0].remote_head)
	except git.exc.GitCommandError:
		print("jtest: Failed to clone git repository")
		sys.exit()

def updateTests(list):
	dir = os.path.abspath(test_dir)
	if not suppress: print("jtest: Test directory: " + dir)

	# Check if basic test files are still there
	for test, paths in list.items():
		if debug: print("jtest: Copying %s into %s" % (paths[1], paths[0]))
		shutil.copy(paths[1], paths[0])

def updateCMake(cmake_dir, new_dir):
	if not suppress: print("jtest: Updating CMake")
	if os.path.isdir(new_dir):
		if not suppress: print("jtest: Deleting %s" % new_dir)
		shutil.rmtree(new_dir)
	if not suppress: print("Copying %s into %s" % (cmake_dir, new_dir))
	copyDirectory(cmake_dir, new_dir)

def runTest(name, paths):
	print("\n####################  Test: %s  ####################" % name)
	if not suppress: print("jtest: Running test %s from file %s" % (name, paths[1]))
	res = make(paths[2], test_dir)

	if not suppress: print("jtest: Executing %s" % (paths[0] + os.sep + paths[2]))
	if valgrind:
		command = ["valgrind", "--leak-check=full", "--show-leak-kinds=all", paths[0] + os.sep + paths[2]]
	elif gdb:
		command = ["gdb", paths[0] + os.sep + paths[2]]
	else:
		command = paths[0] + os.sep + paths[2]
	p = subprocess.Popen(command, cwd=test_dir)
	p.wait()

def make(test, dir):
	if not suppress: print("jtest: Running: make %s\n" % test)
	p = subprocess.Popen(["make", test], cwd=dir, stdout=subprocess.PIPE)
	while True:
		line = p.stdout.readline().rstrip()
		if not line:
			break
		print(line.decode("utf-8"))
		if b"failed" in line or b"error" in line or b"Error" in line:
			if not suppress: print("jtest: Errors detected while compiling, stopping")
			sys.exit()

	p.wait()
	return p.stdout

def cmake(dir):
	if not suppress: print("jtest: Running cmake in directory %s\n" % dir)
	p = subprocess.Popen(["cmake", "CMakeLists.txt"], cwd=dir, stdout=subprocess.PIPE)
	while True:
		line = p.stdout.readline().rstrip().decode("utf-8")
		if not line:
			break
		print(line)
		if "failed" in line or "error" in line or "Error" in line:
			if not suppress: print("jtest: Errors detected while compiling, stopping")
			sys.exit()
	p.wait()

def test_all(dir):
	if not suppress: print("jtest: Running: make check")
	p = subprocess.Popen(["make", "check"], cwd=dir, stdout=subprocess.PIPE)
	while True:
		line = p.stdout.readline().rstrip().decode("utf-8")
		if not line:
			break
		print(line)

	p.wait()
	return p.stdout

def checkForUpdate():
	if not suppress: print("jtest: Checking for script updates in git repo")
	if debug: print("jtest: Comparing hashes of %s and %s" % (script_path, git_script))
	if hashFile(script_path) != hashFile(git_script):
		updateSelf()

def updateSelf():
	if not suppress: print("jtest: Updating self")
	shutil.copy(git_script, script_path)

	#https://stackoverflow.com/a/5758926
	args = sys.argv[:]
	if not suppress: print('jtest: Re-spawning %s\n' % ' '.join(args))

	args.insert(0, sys.executable)
	if sys.platform == 'win32':
		args = ['"%s"' % arg for arg in args]

	if debug: print("jtest: Respawning script in dir %s" % os.path.realpath(script_dir))
	os.chdir(os.path.realpath(script_dir))
	os.execv(sys.executable, args)

# https://stackoverflow.com/a/22058673
def hashFile(file):
	md5 = hashlib.md5()

	with open(file, 'rb') as f:
		for line in f:
			md5.update(line)
	return md5.hexdigest()

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description='JTest Script - HW3')
	test_args = parser.add_argument_group('test arguments')
	advanced_args = parser.add_argument_group('advanced arguments')

	parser.add_argument('-s', '--suppress', help='Suppress status messages', action='store_true', required=False, default=False)
	parser.add_argument('-d', '--debug', help='Enable debug messages', action='store_true', required=False, default=False)
	parser.add_argument('-v', '--version', action='version', version="JTest HW3 " + version)
	parser.add_argument('--credits', help='Print credits and exit', action='store_true', required=False, default=False)

	test_args.add_argument('-a','--all', help='Run all HW3 test cases', action='store_true', required=False, default=False)
	test_args.add_argument('-t','--test', help='Runs individual test case', choices=["stack","parser"], required=False, default="")
	test_args.add_argument('-p','--pull', help='Pull test repo only', action='store_true', required=False, default=False)
	test_args.add_argument('-nv','--novalgr', help="Don't run valgrind on tests", action='store_true', required=False, default=False)
	test_args.add_argument('-g','--gdb', help="Run gdb on test cases. Helpful for tracing segfaults. Does not run valgrind", action='store_true', required=False, default=False)
	test_args.add_argument('-u','--uninstall', help="Remove jtest files and exit", action='store_true', required=False, default=False)

	advanced_args.add_argument('-np','--nopull', help="Don't pull repository", action='store_true', required=False, default=False)
	advanced_args.add_argument('-nu','--noupdate', help="Don't update tests", action='store_true', required=False, default=False)
	advanced_args.add_argument('-ns','--noself', help="Don't update self", action='store_true', required=False, default=False)

	advanced_args.add_argument('--gitdir', help='Override git directory (relative path)', required=False, default="")
	advanced_args.add_argument('--testdir', help='Override tests directory (relative path)', required=False, default="")

	args = parser.parse_args()

	if args.credits:
		print_credits()
		sys.exit()

	if args.testdir == "":
		if script_path.split(os.sep)[-2] != "hw3":
			print("jtest: Please place this script in your hw-[yourid]/hw3 directory")
			sys.exit()

	print_banner("JTest HW3");
	print_credits();
	print("");

	pull_only = args.pull
	no_pull = args.nopull

	suppress = args.suppress
	debug = args.debug
	valgrind = not args.novalgr

	gdb = args.gdb
	if gdb:
		valgrind = False

	if gdb and args.all:
		print("-! --gdb is incompatible with --all")
		sys.exit()
	if args.test == "" and gdb:
		print("-! --gdb requires a test to be set using --test")
		sys.exit()
	if args.pull and args.nopull:
		print("-! --pull and --nopull are mutually exclusive options")
		sys.exit()
	if args.all and args.test != "":
		print("-! --all and --test are mutually exclusive")
		sys.exit()

	if args.gitdir == "":
		git_dir = ".." + os.sep + ".." + os.sep + "csci104-tests"
	else:
		git_dir = args.gitdir

	if args.testdir == "":
		test_dir = script_dir + os.sep + "hw3-check"
	else:
		test_dir = args.testdir

	git_dir = os.path.abspath(git_dir)
	test_dir = os.path.abspath(test_dir)
	test_to_run = args.test
	force_update = False
	noupdate = args.noupdate

	git_script = os.path.abspath(git_dir + os.sep + "hw3" + os.sep + "jtest_hw3.py")

	if args.uninstall:
		print("jtest: removing test cases")
		print("jtest: running rm -r jtest* in %s" % test_dir)
		p = subprocess.Popen(["rm", "-rf", "jtest*"], cwd=test_dir)
		p.wait()
		print("jtest: done, exiting")
		sys.exit()

	####################### DEFINE TESTS #######################
	test_list = dict()
	test_list["stack"] = [os.path.abspath(test_dir + os.sep + "stack_tests"), os.path.abspath(git_dir + os.sep + "hw3" + os.sep + "hw3-check" + os.sep + "stack_tests" + os.sep + "stack_test.cpp"), "stack_test"]
	test_list["parser"] = [os.path.abspath(test_dir + os.sep + "parser_tests"), os.path.abspath(git_dir + os.sep + "hw3" + os.sep + "hw3-check" + os.sep + "parser_tests" + os.sep + "parser_test.cpp"), "parser_test"]
	###########################################################

	# check if repo exists
	if os.path.isdir(git_dir):
		if not suppress: print("jtest: Found csci104-tests git directory")
	else:
		if not suppress: print("jtest: Git directory csci104-tests not found")
		if not os.path.isdir(git_dir):
			os.makedirs(git_dir)
		git_clone(git_dir)
		force_update = True

	if not no_pull:
		changes = git_pull(git_dir)
	else:
		changes = True

	if not suppress: print("jtest: Checking if CMake needs updating")
	if os.path.isfile(git_dir + os.sep + "hw3" + os.sep + ".jtest"):
		with open(git_dir + os.sep + "hw3" + os.sep + ".jtest", 'r') as f:
			git_version = f.read().strip('\n')
			print("jtest: current: %s, git %s" % (version, git_version))
			if version != git_version:
				updateCMake(git_dir + os.sep + "hw3" + os.sep + "hw3-check",os.path.abspath(test_dir))
				force_update = True
				noupdate = False
	if not os.path.isdir(os.path.abspath(test_dir)):
		updateCMake(git_dir + os.sep + "hw3" + os.sep + "hw3-check",os.path.abspath(test_dir))

	if not noupdate:
		if changes or force_update:
			if not suppress: print("jtest: Updating tests")
			updateTests(test_list)

	if not args.noself:
		checkForUpdate()

	cmake(test_dir)

	if args.test != "":
		runTest(args.test, test_list[args.test])

	if args.all:
		test_all(test_dir)

	print("jtest: Finished")
	print_banner("Have a nice day!");
