#!/usr/bin/python

class father:
	def __init__(self,age):
		self.age=age
		print "This is father class initialize!"

class son(father):
	def __init__(self,name,age):
		self.name=name
		print "This is son class initialize!"
		father.__init__(self,age)

if __name__=='__main__':
#if __name__== "__main__":
	a=son("xudifsd",18)
	print a.name
	print a.age
