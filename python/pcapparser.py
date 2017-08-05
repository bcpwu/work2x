#!/usr/bin/python
import os
import sys
import time
import datetime
import pprint 

import dpkt

def parse_pcap_file(fpath):
	f = open(fpath, 'rb')
	pcap = dpkt.pcap.Reader(f)

	for ts, buf in pcap:
		print(len(buf))
		#eth = dpkt.ethernet.Ethernet(buf)
		eth = dpkt.sll.SLL(buf)
		ip = eth.data
		tcp = ip.data
		print(tcp)

		
	f.close()

if len(sys.argv) < 2:
	print('usage:', sys.argv[0], '[filename]' )
	sys.exit(2)

pcap_file = sys.argv[1]
parse_pcap_file(pcap_file)
