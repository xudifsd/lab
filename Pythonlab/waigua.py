#!/usr/bin/python
turn =1
i=9;j=5;k=10;l=10
while True:
    while turn==1:
        i=i-1;j=j+1
        print i
        print j
        turn =2
    while turn==2:
        k=k+1;l=l+1
        print k
        print l
        turn=1
