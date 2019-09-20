#!/usr/bin/env python
import eventlet
from pymhash.pymhash import BackgroundTask
import random
from time import sleep

def handle():
    print("client connected")
    bg = BackgroundTask()
    # for i in range(0,random.randint(10,25)):
    for i in range(0, 150000):
        bg.update("a")
    bg.update("")
    result = bg.result()
    print("EOF result = {0}".format(result))

def main():
    pool = eventlet.GreenPool()
    for i in range(1, 2):
        pool.spawn_n(handle)
    pool.waitall()

if __name__ == '__main__':
    main()
