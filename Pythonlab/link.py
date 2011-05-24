#!/usr/bin/python
class chain:
    '''This class is depends on link class.'''
    def __init__(self,value,next=None):
        self.value=value
        self.next=next
class link:
    '''This can creat a link.But this isn't good to be used by other,there are so
    many print, you can change this print to return.'''
    def __init__(self):
        self.length=0
        self.head=None
    def insert(self,key): #For upwards sequence.
        '''You can use this method to creat upwards sequence.'''
        if self.head==None: #if link is empty.
            self.head=chain(key)
            self.length+=1
            return
        else:
            if self.length==1: #if there are only one key.
                if key>self.head.value:
                    self.head.next=chain(key)
                    self.length+=1
                    return
                else:
                    temp=self.head
                    self.head=chain(key,temp)
                    self.length+=1
                    return
            else:
                if key<=self.head.value: #if key<=the first one of link.
                    temp=self.head
                    self.head=chain(key,temp)
                    self.length+=1
                    return
                p1=self.head
                p2=self.head
                while (key>p1.value) and (p1.next!=None):
                    p2=p1
                    p1=p1.next
                if key>p1.value: #p1 pointer to the last one but key>p1.value.
                    p1.next=chain(key)
                    self.length+=1
                    return
                else:
                    p2.next=chain(key,p1)
                    self.length+=1
                    return
    def remove(self,key):
        '''This method will remove the first found key in the link.'''
        if self.length==0:
           print 'Empty link!' 
           return
        elif self.length==1:
            if key==self.head.value:
                self.head=None
                self.length-=1
                return
            else:
                print '%d is not found in link!'%key
                return
        elif key==self.head.value:
            temp=self.head.next
            self.head=temp
            self.length-=1
            return
        else:
            p1=self.head
            p2=self.head
            while (key>p1.value)and(p1.next!=None):
                p2=p1
                p1=p1.next
            if key==p1.value:#no matter whether there are next chain after p1.
                p2.next=p1.next
                self.length-=1
                return
            else:
                print '%d is not found in link!'%key
                return
    def printall(self):
        '''This method is to test whether link class is tight.'''
        if self.length==0:
            print 'Empty link!'
        else:
            p=self.head
            while p!=None:
                print p.value,
                p=p.next
            print ''
if __name__=='__main__':
    a=link()
    a.insert(100)
    a.insert(2)
    a.insert(3)
    a.insert(3)
    a.printall()
