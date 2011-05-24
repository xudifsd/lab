#!/usr/bin/python
#This program is used to play song by mplayer
#it needs a list, the directory of list is '/home/xudifsd/music'

#CreatedDate: 2010-07-07	Author: xudifsd

#2010-07-08 Notice this modify , program can play without list.
#2010-07-09 Notice this modify , it can add comment(which line starts with #) in list file.
#2010-09-24 this modify make use of argumentsParse , and it can use -n argument to play music in Music's subdir.

#2010-09-25 IMPORTANT UPDATE ! This modify use pyglet and Avbin to play instead of call mplayer	!!!!!


import os
import sys
import random
from argumentsParse import argumentsParse 

#design player from myself , depends on pyglet and Avbin.
def play(song):
	import pyglet
	music = pyglet.media.load(song)
	music.play()

	pyglet.app.run()

ERRORMESSAGE='''
Argument:
--nolist or -n			Directly play music in ~/Music.
--list or -l		list all list that in ~/musiclist
path_of_listname	Play music in list.
'''

#parse arguments

if len(sys.argv)==1:	#user did not input arguments
	print ERRORMESSAGE

elif len(sys.argv)==2:	#this version can only accept 1 arguments
	arguments=argumentsParse(sys.argv[1:])

	if len(arguments[0]) == 1:	#if argument starts with '--' , this mean user use long argument
		argument=arguments[0][0][2:]

		if argument=='nolist':	#if user neednot list
			list=['/home/xudifsd/Music/'+i for i in os.listdir('/home/xudifsd/Music/') if os.path.isfile('/home/xudifsd/Music/'+i )]
			dirs=[i for i in os.listdir('/home/xudifsd/Music/') if os.path.isdir('/home/xudifsd/Music/'+i)]
			for dir in dirs:	#add music in subdir
				list+=['/home/xudifsd/Music/'+dir+'/'+i for i in os.listdir('/home/xudifsd/Music/'+dir) if os.path.isfile('/home/xudifsd/Music/'+dir+'/'+i)]
		elif argument=='list':	#user need to know the name of all list
			list=os.listdir('/home/xudifsd/musiclist/')
			print '\n'.join(list)
			sys.exit()
		else:
			print ERRORMESSAGE
			sys.exit()

	elif len(arguments[1])==1:	#if argumen start with '-' , this mean user use short argument
		argument=arguments[1][0][1:]

		if argument=='n':	#if user neednot list
			list=['/home/xudifsd/Music/'+i for i in os.listdir('/home/xudifsd/Music/') if os.path.isfile('/home/xudifsd/Music/'+i )]
			dirs=[i for i in os.listdir('/home/xudifsd/Music/') if os.path.isdir('/home/xudifsd/Music/'+i)]
			for dir in dirs:	#add music in subdir
				list+=['/home/xudifsd/Music/'+dir+'/'+i for i in os.listdir('/home/xudifsd/Music/'+dir) if os.path.isfile('/home/xudifsd/Music/'+dir+'/'+i)]
		elif argument=='l':	#user need to know the name of all list
			list=os.listdir('/home/xudifsd/musiclist/')
			print '\n'.join(list)
			sys.exit()
		else:
			print ERRORMESSAGE
			sys.exit()

	elif len(arguments[3])==1:	#user make list name as argument
		listname=arguments[3][0]

		try:
			f=open(listname)
		except:
			print 'Please input legal list filename'
			sys.exit()
		else:
			txt=f.read()
			f.close()
			list=txt.split('\n')
			list=[song for song in list if not song.startswith('#')]	#this makes it legal to add comment in list file
			del txt
#play
	while True:
		song=list[random.randint(0,len(list)-1)]	#random select song to play
#		print "mplayer '"+song+"' &>/dev/null"###############################################
		print 'Playing '+song.split('/')[-1]
		play(song)
#		os.system("mplayer '"+song+"'")	#because of this all the song must be an absolute path
#		import time	#################################################
#		time.sleep(1)
