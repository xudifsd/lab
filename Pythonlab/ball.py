#!/usr/bin/python
import time
def ball():
    print'  **'
    print' *  *'
    print'*    *'
    print' *  *'
    print'  **'
for i in range(1,16):
    print'\n'*i,
    ball()
    print'\n'*(16-i),
    time.sleep(0.06)
