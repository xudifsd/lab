#!/usr/bin/python
def binsearch(arr,target):
    low=0
    up=len(arr)-1
    if arr[0]<arr[1]:
        flag=1      #For array is upward sequence,like[1,2,3,4,5]
    else:
        flag=0  #For array is downward sequence,like[5,4,3,2,1]
    while low<=up:
        mid=(low+up)/2
        if target>arr[mid]:
            if flag:
                low=mid+1
            else:
                up=mid-1
        elif target<arr[mid]:
            if flag:
                up=mid-1
            else:
                low=mid+1
        else:
            return mid
    return None
if __name__=='__main__':
    a=['ad','b','c','d']
    #for i in range(10000000):
     #   a.append(i)
    target=raw_input('Enter:\n')
    print binsearch(a,target)
