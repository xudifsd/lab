#!/usr/bin/python
def sort(arr):
    '''This function help make element in array sorted to upwards sequence.'''
    size=len(arr)
    for times in range(1,size+1):
        for i in range(0,size-1):
            if arr[i]>arr[i+1]:
                a=arr[i+1]
                arr[i+1]=arr[i]
                arr[i]=a
    return arr
if __name__=='__main__':
    arr=[]
    while 1:
        try:
            x=int(raw_input('Enter numbers:\n'))
        except ValueError:
            break
        arr.append(x)
        print sort(arr)