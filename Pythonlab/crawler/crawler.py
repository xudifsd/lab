#!/usr/bin/python3
#Date : 2010-11-05 Author : xudifsd
#2010-11-06 rewrite crawler , use database and regular expression and thread

import re
from urllib.parse import urlparse
import sqlite3
import threading
import time
from opener import urlopen

class crawler:
	'''this class is crawl the web page and save it in database'''
	def __init__(self,url,internal=True,limit=10,database='page.sqlite3'):
		print('__init__') #########################
		self.internal=internal	#only crawl internal page if True
		self.limit=limit	#only crawl limited pages
		self.target=[url]	#it store url that will be crawled it's FIFO , and it out from end
		self.savedurl=[]	#it store url that already saved
		self.database=database

		self.linkPattern=re.compile(r'<[aA] href="(http://.*?)[#?&]?"')	#link
		self.internalPattern=re.compile(r'<[a|A] href="(/.*?)"')	#internal link

		rooturl=urlparse(url)
		self.netloc=rooturl.netloc	#this store net location
		self.scheme=rooturl.scheme	#this store net scheme

		try:
			self.createdb()	#create database first
		except Exception as e:
			print(self.database+' is already there')	#########################
	def isinternal(self,url):
		if self.netloc == urlparse(url).netloc:
			return True
		else:
			return False
	def parsePage(self,content):	#abstract link from page exclude saved page
		print(threading.currentThread().name+' parsePage ') ############################

		internallink=self.internalPattern.findall(content)
		self.target=list((self.scheme+'://'+self.netloc+link for link in internallink))+self.target

		sublink=self.linkPattern.findall(content)
		if self.internal:
			self.target=list((link for link in sublink if self.isinternal(link)))+self.target	#it is FIFO not FILO
		else:
			self.target=sublink+self.target	#it is FIFO not FILO
		self.target=list((link for link in self.target if link not in self.savedurl))	#exclude saved page
	def createdb(self):
		conn=sqlite3.connect(self.database)
		cur=conn.cursor()
		cur.execute('create table netpage (content text,url varchar(100))')
		conn.commit()
		conn.close()
		print('created database : '+self.database) ############################
	def crawl(self):
		print(threading.currentThread().name+' start crawl!!!!!!!!') #######################
		for times in range(0,self.limit):
			try:
				url=self.target.pop()	#it is FIFO not FILO
			except IndexError as e:
				print(threading.currentThread().name+' IndexError!!!')
			else:
				print(threading.currentThread().name+' is crawling '+url) ####################
				try:
					page=urlopen(url)
				except Exception as e:
					print(e) #############
				else:
					try:
						content=page.read().decode('utf-8')
					except Exception as e:
						page.seak(0)
						try:
							content=page.read().decode('gbk')
						except Exception as ie:
							print('page is not encoded by utf-8 nor gbk')
							continue
					self.parsePage(content)	#abstract link
					conn=sqlite3.connect(self.database)
					cur=conn.cursor()
					args=(content,url)
					cur.execute('insert into netpage values(?,?)',args)
					conn.commit()
					conn.close()
					self.savedurl.append(url)
					print(threading.currentThread().name+' saved page of '+url) ####################


if __name__=='__main__':
	testurl='http://woodpecker.org.cn/'
	a=crawler(testurl,limit=20)
	t1=threading.Thread(target=a.crawl,name='1')
	t2=threading.Thread(target=a.crawl,name='2')
	t3=threading.Thread(target=a.crawl,name='3')
	
	t1.start()
	time.sleep(20)	#t1 download and parse root page
	t2.start()
	t3.start()
