import subprocess
import string
import git
import sys
import os
import argparse
from shutil import copy
import hashlib

repo_url = "https://github.com/jholtmann/csci104-tests"
script_dir = os.path.dirname(os.path.realpath(__file__))
script_path = os.path.realpath(__file__)

class bcolors:
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKGREEN = '\033[92m'
	WARNING = '\033[93m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'

def git_pull(gdir):
	try:
		if not suppress: print("-- Pulling repo %s" % gdir)
		repo = git.Repo(gdir)
		hash = repo.head.object.hexsha
		o = repo.remotes.origin
		o.pull(o.refs[0].remote_head)

		if repo.head.object.hexsha != hash:
			return True
		else:
			return False
	except git.exc.GitCommandError:
		print("-- Failed to pull git repository")
		sys.exit()

def git_clone(gdir):
	try:
		if not suppress: print("-- Cloning %s into %s" % (repo_url, gdir))
		repo = git.Repo.init(gdir)
		origin = repo.create_remote('origin', repo_url)
		origin.fetch()
		origin.pull(origin.refs[0].remote_head)
	except git.exc.GitCommandError:
		print("-- Failed to clone git repository")
		sys.exit()

def updateTests(list):
	dir = os.path.abspath(test_dir)
	if not suppress: print("-- Test directory: " + dir)

	# Check if basic test files are still there
	for test, paths in list.items():
		ind_path = paths[0] + os.sep + "basic_tests.cpp"
		if os.path.isfile(ind_path):
			if not suppress: print("-- Found %s" % ind_path)
			if not suppress: print("-- Removing %s" % ind_path)
			os.remove(ind_path)
		if debug: print("-- Copying %s into %s" % (paths[1], paths[0]))
		copy(paths[1], paths[0])
	cmake(test_dir)

def runAll(list):
	make("check", test_dir)
	# for test, paths in list.items():
	# 	runTest(test, paths)

def runTest(name, paths):
	print("\n#######################  Test: %s  #######################" % name)
	if not suppress: print("-- Running test %s from file %s" % (name, paths[1]))
	res = make(paths[2], test_dir)

	run = True
	if "failed" in res:
		run = False

	if run:
		if not suppress: print("-- Executing %s" % (paths[0] + os.sep + paths[2]))
		p = subprocess.Popen(["valgrind", "--leak-check=full", "--show-leak-kinds=all", paths[0] + os.sep + paths[2]], cwd=test_dir)
		p.wait()
	else:
		if not suppress: print("-- Errors detected while compiling, stopping")
		sys.exit()

def make(test, dir):
	if not suppress: print("-- Running: make %s\n" % test)
	p = subprocess.Popen(["make", test], cwd=dir, stdout=subprocess.PIPE)
	p.wait()
	return p.stdout

def cmake(dir):
	if not suppress: print("-- Running cmake in directory %s\n" % dir)
	p = subprocess.Popen(["cmake", "CMakeLists.txt"], cwd=dir)
	p.wait()

def checkForUpdate():
	if not suppress: print("-- Checking for script updates in git repo")
	if debug: print("-- Comparing hashes of %s and %s" % (script_path, git_script))
	if hashFile(script_path) != hashFile(git_script):
		updateSelf()

def updateSelf():
	if not suppress: print("-- Updating self")
	copy(git_script, script_path)

	#https://stackoverflow.com/a/5758926
	args = sys.argv[:]
	if not suppress: print('-- Re-spawning %s\n' % ' '.join(args))

	args.insert(0, sys.executable)
	if sys.platform == 'win32':
		args = ['"%s"' % arg for arg in args]

	if debug: print("-- Respawning script in dir %s" % os.path.realpath(script_dir))
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
	parser = argparse.ArgumentParser(description='JTest Script - HW2')
	required = parser.add_argument_group('required arguments')

	parser.add_argument('-a','--all', help='Run all HW2 test cases', action='store_true', required=False, default=False)
	parser.add_argument('-t','--test', help='Runs individual test case', choices=["ssort","clist","duckduck"], required=False, default="")
	parser.add_argument('-p','--pull', help='Pull test repo only', action='store_true', required=False, default=False)
	parser.add_argument('-np','--nopull', help="Don't pull repository", action='store_true', required=False, default=False)
	parser.add_argument('-nu','--noupdate', help="Don't update tests", action='store_true', required=False, default=False)
	parser.add_argument('-ns','--noselfupdate', help="Don't update self", action='store_true', required=False, default=False)
	parser.add_argument('--gitdir', help='Override git directory (relative path)', required=False, default="")
	parser.add_argument('--testdir', help='Override tests directory (relative path)', required=False, default="")
	parser.add_argument('-d', '--debug', help='Enable debug messages', action='store_true', required=False, default=False)
	parser.add_argument('-s', '--suppress', help='Suppress status messages', action='store_true', required=False, default=False)

	args = parser.parse_args()

	if args.testdir == "":
		if (not (script_path.split(os.sep)[-2].split('-')[-1] != "hw" and
			script_path.split(os.sep)[-1] != "hw2")):
			print("-- Please place this script in your hw-[yourid]/hw2 directory")
			sys.exit()

	print("####################################################")
	print("                   JTEST HW2              ")
	print("####################################################")

	pull_only = args.pull
	no_pull = args.nopull

	if args.pull and args.nopull:
		print("-- --pull and --nopull are mutually exclusive options")
		sys.exit()
	if args.all and args.test != "":
		print("-- --all and --test are mutually exclusive")
		sys.exit()

	if args.gitdir == "":
		git_dir = ".." + os.sep + ".." + os.sep + "csci104-tests"
	else:
		git_dir = args.gitdir

	if args.testdir == "":
		test_dir = script_dir + os.sep + "hw2-check"
	else:
		test_dir = args.testdir

	suppress = args.suppress
	debug = args.debug

	git_dir = os.path.abspath(git_dir)
	test_dir = os.path.abspath(test_dir)
	test_to_run = args.test
	force_update = False

	git_script = os.path.abspath(git_dir + os.sep + "hw2" + os.sep + "jtest_hw2.py")

	####################### DEFINE TESTS #######################
	test_list = dict()
	test_list["ssort"] = [os.path.abspath(test_dir + os.sep + "selection_sort_tests"), os.path.abspath(git_dir + os.sep + "hw2" + os.sep + "jtest-ssort.cpp"), "selection_sort_test"]
	test_list["clist"] = [os.path.abspath(test_dir + os.sep + "circular_list_tests"), os.path.abspath(git_dir + os.sep + "hw2" + os.sep + "jtest-clist.cpp"), "circular_list_test"]
	test_list["duckduck"] = [os.path.abspath(test_dir + os.sep + "duck_duck_goose_tests"), os.path.abspath(git_dir + os.sep + "hw2" + os.sep + "jtest-duckduck.cpp"), "duck_duck_goose_test"]
	###########################################################

	# check if repo exists
	if os.path.isdir(git_dir):
		if not suppress: print("-- Found csci104-tests git directory")
	else:
		if not suppress: print("-- Git directory csci104-tests not found")
		if not os.path.isdir(git_dir):
			os.makedirs(git_dir)
		git_clone(git_dir)
		cmake(test_dir)
		force_update = True

	if not no_pull:
		changes = git_pull(git_dir)
	else:
		changes = True

	if not args.noselfupdate:
		checkForUpdate()

	if not args.noupdate:
		if changes or force_update:
			if not suppress: print("-- Updating tests")
			updateTests(test_list)

	if args.test != "":
		runTest(args.test, test_list[args.test])

	if args.all:
		runAll(test_list)
