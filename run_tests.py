import os
import time


def print_line():
	print('=' * 90)

	
def print_description(fullpath):
	lines = [line.rstrip('\n') for line in open(fullpath) if line[0] == '#']
	if len(lines):
		print_line()
		for line in lines: 
			print(line)


def absolute_file_paths(directory):
   for dirpath,_,filenames in os.walk(directory):
       for f in filenames:
           yield os.path.abspath(os.path.join(dirpath, f)), f


def test_file(fullpath, title):
	cmd = interpreter_path + ' ' + fullpath
	
	print_line()
	print('Starting test \'' + title + '\'')
	print_description(fullpath)
	print_line()
	
	time.sleep(2)
	os.system(cmd)
	
	print_line()
	print('Ended test \'' + title + '\'')
	print_line()
	
	input("Enter to continue")
	print('\n')
		   
		   
def test_folder(directory):
	for fullpath, filename in absolute_file_paths(directory):
		test_file(fullpath, directory + filename)
	
	
interpreter_path = 'tkom_interpreter.exe -e'

os.system('cls')
print('Starting tests...')
test_folder('tests/bad/')
test_folder('tests/good/')
print('Tests ended...')