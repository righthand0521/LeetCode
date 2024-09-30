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


class CustomStack:
    def __init__(self, maxSize: int):
        self.stack = deque()
        self.maxSize = maxSize

    def push(self, x: int) -> None:
        stackSize = len(self.stack)
        if stackSize < self.maxSize:
            self.stack.append(x)

    def pop(self) -> int:
        # Pops and returns the top of the stack or -1 if the stack is empty.
        retVal = -1

        if self.stack:
            retVal = self.stack.pop()

        return retVal

    def increment(self, k: int, val: int) -> None:
        for i, _ in zip(range(k), self.stack):
            self.stack[i] += val


# Your CustomStack object will be instantiated and called as such:
# obj = CustomStack(maxSize)
# obj.push(x)
# param_2 = obj.pop()
# obj.increment(k,val)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in zip([["CustomStack", "push", "push", "pop", "push", "push", "push", "increment",
                                     "increment", "pop", "pop", "pop", "pop"]],
                                   [[[3], [1], [2], [], [2], [3], [4], [5, 100], [2, 100], [], [], [], []]]):
            # /* Example
            #  *  Input
            #  *  ["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
            #  *  [[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
            #  *  Output
            #  *  [null,null,null,2,null,null,null,null,null,103,202,201,-1]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "CustomStack":
                    obj = CustomStack(value[0])
                    displayStr.append(None)
                elif key == "push":
                    retVal = obj.push(value[0])
                    displayStr.append(None)
                elif key == "pop":
                    retVal = obj.pop()
                    displayStr.append(retVal)
                elif key == "increment":
                    retVal = obj.increment(value[0], value[1])
                    displayStr.append(None)
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
