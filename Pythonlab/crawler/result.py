#!/usr/bin/python3
#Date : 2010-11-05 Author : xudifsd
#2010-11-05 this model is used to select netpage from database which created by crawler.py

import sqlite3

def result(database='page.sqlite3'):
	conn=sqlite3.connect(database)
	cur=conn.cursor()
	cur.execute('select * from netpage')
	name=1
	for i in cur:
		f=open('%d.html'%name,'w')
		f.write(i[0])
		f.close()
		name+=1
	conn.close()

if __name__=='__main__':
	result()
