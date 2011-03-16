#!/usr/bin/python
class Node:
    '''Created for SplayTree class.'''
    def __init__(self,word):
        self.word=word
        self.count=1
        self.left_node=None
        self.right_node=None
class SplayTree:
    def __init__(self):
        self.root=None
        self.sum=0      #sum is the sum of all words.
        self.__top10=[]      #this is created for top10().
    def insert(self,word):
        if self.root==None:#If tree is empty.
            self.root=Node(word)
            self.sum+=1
            return
        else:
            p=self.root #p is a pointer.
            while 1:
                if p.word == word :
                    p.count+=1
                    self.sum+=1
                    return
                elif p.word > word:
                    if p.left_node == None:
                        p.left_node=Node(word)
                        self.sum+=1
                        return
                    else:
                        p=p.left_node
                        continue
                elif p.word < word:
                    if p.right_node == None:
                        p.right_node=Node(word)
                        self.sum+=1
                        return
                    else:
                        p=p.right_node
                        continue
    def printall(self,address='First'):#if printall is not called by itself,address='First'.
        if address == 'First':
            p=self.root
        else:
            p=address
        if p.left_node != None:
            self.printall(p.left_node)
        print p.word,
        print '\t',
        if p.right_node != None:
            self.printall(p.right_node)

    def top10(self,address='First'):#if top10 is not called by itself,address='First'.
        if address == 'First':
            p=self.root
        else:
            p=address
        if p.left_node != None:
            self.top10(p.left_node)
        
        arr=[]
        arr.append(p.word)
        arr.append(p.count)
        if len(self.__top10) < 10:
            self.__top10.append(arr)
        else:
            min=self.__top10[0]
            for i in self.__top10:    #find the mixest in self.__top10.
                if i[1] < min[1]:
                    min=i
            if arr[1] > min[1]:
                self.__top10.remove(min)
                self.__top10.append(arr)
        
        if p.right_node != None:
            self.top10(p.right_node)
        return self.__top10
if __name__=='__main__':
    a=SplayTree()
    a.insert('a')
    a.insert('b')
    a.insert('1')
    a.printall()
