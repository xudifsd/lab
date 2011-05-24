#!/usr/bin/python3
import sys

class MatrixError(Exception):
	'''If you need square matrix , it didn't provide , this exception raised.'''
	def __init__(self):
		Exception.__init__(self)

class RowLengthError(Exception):
	'''If length of matrix's row didn't match , this exception raised.'''
	def __init__(self,exceptlen):
		Exception.__init__(self)
		self.exceptlen=exceptlen

class EmptyMatrixError(Exception):
	'''If matrix is empty , this exception raised.'''
	def __init__(self):
		Exception.__init__(self)

class Matrix:
	def __init__(self):
		self.__data=[]
	def addrow(self,row):
		if len(self.__data)==0:	#it is a empty matrix
			self.__data.append(row[:])
		else:
			if len(self.__data[0]) == len(row):	#the length of each row must be same
				self.__data.append(row[:])
			else:
				raise RowLengthError(len(self.__data[0]))
	def transmit(self):
		if len(self.__data) == 0:
			raise EmptyMatrixError
		if len(self.__data) != len(self.__data[0]):
			raise MatrixError
		result=self.__data[:]
		n=len(result)
		for i in range(0,n):
			for j in range(0,n):
				if result[j][i] == 1:
					for k in range(0,n):
						result[j][k]=result[j][k] or result[i][k]
		return result
	def __str__(self):
		result=''
		for row in range(0,len(self.__data)):
			result+=str(self.__data[row])
			result+='\n'
		return result

if __name__ == '__main__':
	test=Matrix()
	while True:
		row=input("Enter one row of matrix:\n")
		if len(row) == 0:
			break
		try :
			test.addrow(list(float(i) for i in row.split(' ')))	#the matrix only store float
		except RowLengthError as e:
			sys.stderr.write("Row length is not matched , you should input row with length of %d!\n"%e.exceptlen)
	try:
		result=test.transmit()
	except MatrixError:
			sys.stderr.write("You should provide square matrix!\n")
	except EmptyMatrixError:
			sys.stderr.write("The matrix is empty!\n")
	else:			
		for i in range(0,len(result)):
			print(result[i])

