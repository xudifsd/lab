#!/usr/bin/python
import os
result=[]
def filesearch(target,source):
    """This function helps you find files that have exact word in its name,good luck!"""
    try:
        all=os.listdir(source)
    except:
        pass
    else:
        file=[os.path.normcase(a) for a in all if os.path.isfile(source+a)]
        dir=[b for b in all if b not in file]
        for i in file:
            if target in i:
                result.append(source+i)
        for j in dir:
            filesearch(target,source+j+os.sep)
if __name__=='__main__':
    print 'This program is in test version.'
    print ''
    target=raw_input('Enter what you want to search for:\n')
    source=raw_input('Enter where you want to search:\n')
    print '\n\n'
    filesearch(target,source)
    print '\n'.join(result)
    print 'There are %d file(s) in match.'%len(result)
