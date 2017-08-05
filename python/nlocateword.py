#!/usr/bin/python3
import os
import sys

def print_file(fpath):
	file = open(fpath)
	lines = file.readlines()
	for line in lines:
		print(line, end='')

def search_file(fpath, word):
#	print(fpath)
	lineno = 0
	file = open(fpath)
	lines = file.readlines()
	for line in lines:
		lineno += 1
		if line.find(word) > -1:
			print(fpath, '[', lineno, ']:', line, end=' ')
	file.close()

def search_file(fpath, word):
#	print(fpath)
	lineno = 0
	found = False
	file = open(fpath)
	lines = file.readlines()
	for line in lines:
		lineno += 1
		if line.find(word) > -1:
			found = True
	file.close()
	if not found:
		print(fpath, '[', lineno, ']:', end='\n')

conf_files = ['*']

#print('arg num:', len(sys.argv))
#print('args:', str(sys.argv))

if len(sys.argv) < 2:
	print('usage:', sys.argv[0], '[search_word]', end='\n' )
	sys.exit(2)
	
sword = sys.argv[1]
print('search for:', sword, end='\n')

for (dirname, subshere, fileshere) in os.walk('.'):
#	print('[' + dirname + ']')
	for fname in fileshere:
		fpath = os.path.join(dirname, fname)
#		print(fpath)
		#for conf in conf_files:
			#if fname.endswith(conf):
		search_file(fpath, sword)

		
		