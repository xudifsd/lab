#!/usr/bin/python3
import threading
class tt:
	def __init__(self,ticket):
		self.ticket=ticket
	def demo(self):
		while self.ticket>0:
			print(threading.currentThread().name+': ticket '+str(self.ticket))
			self.ticket-=1

if __name__=='__main__':
	a=tt(100)
	th1=threading.Thread(target=a.demo,name="1")
	th2=threading.Thread(target=a.demo,name="2")
	th3=threading.Thread(target=a.demo,name="3")

	th1.start()
	th2.start()
	th3.start()
