#!/usr/bin/python3
#https://stackoverflow.com/questions/2600191/how-can-i-count-the-occurrences-of-a-list-item-in-python
import os
import sys
import pprint 

class SortedDisplayDict(dict):
	def __str__(self):
		return "{" + ", ".join("%r: %r" % (key, self[key]) for key in sorted(self)) + "}"

def print_file(fpath):
	file = open(fpath)
	lines = file.readlines()
	for line in lines:
		print(line, end='')


def parse_nmea_log(fpath):
	gsv_counters = {}
	gga_counters = {}
	count_all = 0
	count_gsv = 0
	count_gga = 0
	fd = open(fpath,'r', errors='replace')
	while True:
		try:
			message = fd.readline()
			if not message:
				break;
			count_all = count_all + 1
			#print("message total:", count_all, ", GPGSV #:", count_gsv, ",", message, end='\n')		
			#if 'rawr' in text:
			fields = message.split(",")
			#print(message, end='')
			message_id = fields[0]
			if message_id == "$GPGSV":
				count_gsv = count_gsv + 1
				#print(mylist[3], end='\n')
				#print(mylist, end='\n')
				sv = fields[3]
				if sv in gsv_counters:
					gsv_counters[sv] = gsv_counters[sv]+1
				else:
					gsv_counters[sv] = 1			
			if message_id == "$GPGGA":
				count_gga = count_gga + 1
				#print(mylist[3], end='\n')
				#print(mylist, end='\n')
				sv = fields[7]
				#if sv == '00':
				#	print("[", count_all, "]:", message, end='\n')
				if sv in gga_counters:
					gga_counters[sv] = gga_counters[sv]+1
				else:
					gga_counters[sv] = 1	
		except IOError:
			print("Could not read file:", message, end='\n')
			break
	fd.close()
	print("Total messages:", count_all, ", $GPGSV #:", count_gsv, "$GPGGA #:", count_gga, end='\n')
	#print("gsv counters:", gsv_counters, end='\n')
	print("VSat '#': $GPGSV #", end='\n')
	pprint.pprint(gsv_counters)
	#print("gga counters:", gga_counters, end='\n')
	print("VSat '#': $GPGGA #", end='\n')
	pprint.pprint(gga_counters)
	#d = SortedDisplayDict(gsv_counters)
	#print("VSat/$GPGSV:", d, end='\n')
	#d = SortedDisplayDict(gga_counters)
	#print("VSat/$GPGGA:", d, end='\n')


#print('arg num:', len(sys.argv))
#print('args:', str(sys.argv))

if len(sys.argv) < 2:
	print('usage:', sys.argv[0], '[filename]', end='\n' )
	sys.exit(2)
	
gpsfile = sys.argv[1]
print('raw NMEA log file:', gpsfile, end='\n')

parse_nmea_log(gpsfile)
