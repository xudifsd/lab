#!/usr/bin/python3
#Date : 2010-11-05 Author : xudifsd
#2010-11-05 this model is imported by crawler

import urllib.request

def urlopen(url,uset_agent="Mozilla/5.0"):
	'''This function is used to add user-agent to header of http request.'''
	opener = urllib.request.build_opener()
	opener.addheaders = [('User-agent',uset_agent)]
	page=opener.open(url)
	return page

if __name__=='__main__':
	a=input('input url:\n')
	file=urlopen(a)
	f=open('test.html','w')
	f.write(file.read().decode('utf-8'))
