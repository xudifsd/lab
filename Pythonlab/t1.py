#!/usr/bin/python
import re
import collections
import dxprofile
class Counter(collections.defaultdict):
	def __init__(self,words):
		collection.defaultdice.__init__(self,int)
		for word in words:
			self[word]+=1
word=re.findall(r'\b[a-zA-Z]+\b',open('full.txt').read())
profile.run('Counter(words)')
