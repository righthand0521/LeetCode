import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class MyQueue:
    def __init__(self):
        self.stack = []
        self.stackTmp = []

    def push(self, x: int) -> None:
        while self.empty() == False:
            self.stackTmp.append(self.stack.pop())

        self.stack.append(x)

        while len(self.stackTmp) != 0:
            self.stack.append(self.stackTmp.pop())

    def pop(self) -> int:
        retVal = 0

        if self.empty() == False:
            retVal = self.stack.pop()

        return retVal

    def peek(self) -> int:
        retVal = self.stack[-1]

        return retVal

    def empty(self) -> bool:
        retVal = False

        if len(self.stack) == 0:
            retVal = True

        return retVal


# Your MyQueue object will be instantiated and called as such:
# obj = MyQueue()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.peek()
# param_4 = obj.empty()

if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, num in zip([["MyQueue", "push", "push", "peek", "pop", "empty"]], [[None, 1, 2, None, None, None]]):
            # /* Example
            #  *  Input
            #  *  ["MyQueue", "push", "push", "peek", "pop", "empty"]
            #  *  [[], [1], [2], [], [], []]
            #  *  Output
            #  *  [null, null, null, 1, 1, false]
            #  */
            logging.info("%s", methods)
            displayStr = []
            for p in num:
                if p == None:
                    displayStr.append([])
                else:
                    displayStr.append(p)
            logging.info("%s", displayStr)

            displayStr = []
            obj = MyQueue()
            for p, q in zip(methods, num):
                if p == "MyQueue":
                    displayStr.append(None)
                elif p == "push":
                    obj.push(q)
                    displayStr.append(None)
                elif p == "pop":
                    retVal = obj.pop()
                    displayStr.append(retVal)
                elif p == "peek":
                    retVal = obj.peek()
                    displayStr.append(retVal)
                elif p == "empty":
                    retVal = obj.empty()
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
