import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class Node:
    def __init__(self, val, next=None, prev=None):
        self.val = val
        self.next = next
        self.prev = prev


class MyCircularDeque:
    def __init__(self, k: int):
        self.capacity = k
        self.head = None
        self.rear = None
        self.size = 0

    def insertFront(self, value: int) -> bool:
        retVal = False

        if self.isFull() == True:
            return retVal

        if self.head is None:
            self.head = Node(value, None, None)
            self.rear = self.head
        else:
            newHead = Node(value, self.head, None)
            self.head.prev = newHead
            self.head = newHead
        self.size += 1
        retVal = True

        return retVal

    def insertLast(self, value: int) -> bool:
        retVal = False

        if self.isFull() == True:
            return retVal

        if self.head is None:
            self.head = Node(value, None, None)
            self.rear = self.head
        else:
            self.rear.next = Node(value, None, self.rear)
            self.rear = self.rear.next
        self.size += 1
        retVal = True

        return retVal

    def deleteFront(self) -> bool:
        retVal = False

        if self.isEmpty() == True:
            return retVal

        if self.size == 1:
            self.head = None
            self.rear = None
        else:
            self.head = self.head.next
        self.size -= 1
        retVal = True

        return retVal

    def deleteLast(self) -> bool:
        retVal = False

        if self.isEmpty() == True:
            return retVal

        if self.size == 1:
            self.head = None
            self.rear = None
        else:
            self.rear = self.rear.prev
        self.size -= 1
        retVal = True

        return retVal

    def getFront(self) -> int:
        retVal = -1  # Returns -1 if the deque is empty.

        if self.isEmpty() == False:
            retVal = self.head.val

        return retVal

    def getRear(self) -> int:
        retVal = -1  # Returns -1 if the deque is empty.

        if self.isEmpty() == False:
            retVal = self.rear.val

        return retVal

    def isEmpty(self) -> bool:
        retVal = False

        if self.size == 0:
            retVal = True

        return retVal

    def isFull(self) -> bool:
        retVal = False

        if self.size == self.capacity:
            retVal = True

        return retVal

# Your MyCircularDeque object will be instantiated and called as such:
# obj = MyCircularDeque(k)
# param_1 = obj.insertFront(value)
# param_2 = obj.insertLast(value)
# param_3 = obj.deleteFront()
# param_4 = obj.deleteLast()
# param_5 = obj.getFront()
# param_6 = obj.getRear()
# param_7 = obj.isEmpty()
# param_8 = obj.isFull()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in zip([["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront",
                                     "getRear", "isFull", "deleteLast", "insertFront", "getFront"]],
                                   [[[3], [1], [2], [3], [4], [], [], [], [4], []]]):
            # /* Example
            #  *  Input
            #  *  ["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront",
            #  *  "getRear", "isFull", "deleteLast", "insertFront", "getFront"]
            #  *  [[3], [1], [2], [3], [4], [], [], [], [4], []]
            #  *  Output
            #  *  [null, true, true, true, false, 2, true, true, true, 4]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "MyCircularDeque":
                    obj = MyCircularDeque(value[0])
                    displayStr.append(None)
                elif key == "insertFront":
                    retVal = obj.insertFront(value[0])
                    displayStr.append(retVal)
                elif key == "insertLast":
                    retVal = obj.insertLast(value[0])
                    displayStr.append(retVal)
                elif key == "deleteFront":
                    retVal = obj.deleteFront()
                    displayStr.append(retVal)
                elif key == "deleteLast":
                    retVal = obj.deleteLast()
                    displayStr.append(retVal)
                elif key == "getFront":
                    retVal = obj.getFront()
                    displayStr.append(retVal)
                elif key == "getRear":
                    retVal = obj.getRear()
                    displayStr.append(retVal)
                elif key == "isEmpty":
                    retVal = obj.isEmpty()
                    displayStr.append(retVal)
                elif key == "isFull":
                    retVal = obj.isFull()
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
