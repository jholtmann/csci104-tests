import subprocess
import string
import git
import sys
import os

git_dir = "../../csci104-tests"
script_dir = os.path.dirname(os.path.realpath(__file__))

def git_pull():
	repo = git.Repo(git_dir)
	hash = repo.head.object.hexsha
	o = repo.remotes.origin
	o.pull()

	if repo.head.object.hexsha == hash:
		return True
	else:
		return False

def git_clone():
	repo = git.Repo(git_dir)

if __name__ == "__main__":
	if (script_dir.split('/')[-2].split('-')[-2] != "hw" or
		script_dir.split('/')[-1] != "hw2"):

		print("Please place this script in your hw-[yourid]/hw2 directory")
		sys.exit()

	# res = subprocess.check_output(["ls", "-la"])
	# for line in res.splitlines():
	# 	process the output line by line

	# check if repo exists
	print(os.path.isdir(git_dir))
