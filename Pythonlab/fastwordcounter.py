#!/usr/bin/python
from operator import itemgetter
file=raw_input("Enter source file:\n")
from time import clock
import re
start=clock()
a={}
f=open(file)
txt=f.read()
f.close()
txt=re.compile(r'\b[a-zA-Z]+\b').findall(txt)
for i in txt:
	try:
		a[i]+=1
	except:
		a[i]=1
sum=0
for key in a.keys():
	sum+=a[key]
print sorted(a.iteritems(),key=itemgetter(1),reverse=True)[0:10]
print "There are %d words in %s."%(sum,file)
finish=clock()
print 'Run time is %d.'%(finish-start)
