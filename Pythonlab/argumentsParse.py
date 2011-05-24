#!/usr/bin/python
#Author : xudifsd , CreateDate : 2009-09-24

#THIS FILE IS IMPORT BY MANY PROGRAM IN ~/bin !

'''
form of result:
result[0] is arguments that starts with '--'	i.e. --argu
result[1] is arguments that starts with '-'	i.e. -argu
result[2] is arguments that have '=' in it	i.e. a=argu
result[3] is just a normal arguments		i.e. argu
'''

def argumentsParse(rawArguments):
	#ATTENTION:if you make sys.argv as arguments you should remember that sys.argv[0] maybe not argumen you want
	'''This function is used to parse sys.argv , return is a array that contain 4 item . the 1st item is array , it contains arguments that starts with
 "--" ; 2nd item is array that contains arguments that starts with "-" ; the 3rd item is dictionary which key is arguments before "=" , value is 
arguments after "=" ; the 4th is array , it is normal arguments.'''
	result=[[],[],{},[]]

	result[0]=[i for i in rawArguments if i.startswith('--')]

	result[1]=[i for i in rawArguments if i not in result[0] and i.startswith('-')]

	dicttemp=[i for i in rawArguments if '=' in i]

	for i in dicttemp:
		argument=i.split('=')
		result[2][argument[0]]=argument[1]

	result[3]=[i for i in rawArguments if i not in result[0]+result[1]+dicttemp]	#this contain normal argument

	return result

if __name__=='__main__':
	import sys
	print argumentsParse(sys.argv[1:])
