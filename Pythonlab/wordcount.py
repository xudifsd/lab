#!/usr/bin/python
#encoding=utf-8
file=raw_input("Enter source file:\n")
from time import clock
start=clock()
from SplayTree import *
import re
a=SplayTree()
f=open(file)
txt=f.read()
f.close()
txt=re.compile(r'[^a-z^A-Z]?([a-zA-Z]+)[^a-z^A-Z]?').findall(txt)	#该正则表达式匹配单词，包括a2s中的a和s
for i in txt:
    a.insert(i)
print a.top10()
#a.printall()
print 'There are %d words in %s'%(a.sum,file)
finsih=clock()
print'Run time is %d s'%(finsih - start)
