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


class MinStack:
    def __init__(self):
        self.stack = []
        self.minStack = []

    def push(self, val: int) -> None:
        self.stack.append(val)
        if len(self.minStack) == 0:
            self.minStack.append(val)
        else:
            self.minStack.append(min(val, self.minStack[-1]))

    def pop(self) -> None:
        self.stack.pop()
        self.minStack.pop()

    def top(self) -> int:
        retVal = self.stack[-1]

        return retVal

    def getMin(self) -> int:
        retVal = retVal = self.minStack[-1]

        return retVal

# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(val)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"]],
                                [[[], [-2], [0], [-3], [], [], [], []]]):
            # /* Example
            #  *  Input
            #  *  ["MinStack","push","push","push","getMin","pop","top","getMin"]
            #  *  [[],[-2],[0],[-3],[],[],[],[]]
            #  *  Output
            #  *  [null,null,null,null,-3,null,0,-2]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "MinStack":
                    obj = MinStack()
                    displayStr.append(None)
                elif key == "push":
                    obj.push(value[0])
                    displayStr.append(None)
                elif key == "pop":
                    obj.pop()
                    displayStr.append(None)
                elif key == "top":
                    retVal = obj.top()
                    displayStr.append(retVal)
                if key == "getMin":
                    retVal = obj.getMin()
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
