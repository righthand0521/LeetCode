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


class MyStack:
    def __init__(self):
        self.useQueue = deque()
        self.tempQueue = deque()

    def push(self, x: int) -> None:
        self.tempQueue.append(x)
        while self.useQueue:
            self.tempQueue.append(self.useQueue.popleft())

        self.useQueue, self.tempQueue = self.tempQueue, self.useQueue

    def pop(self) -> int:
        retVal = self.useQueue.popleft()

        return retVal

    def top(self) -> int:
        retVal = self.useQueue[0]

        return retVal

    def empty(self) -> bool:
        retVal = True
        if self.useQueue:
            retVal = False

        return retVal

# Your MyStack object will be instantiated and called as such:
# obj = MyStack()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.top()
# param_4 = obj.empty()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["MyStack", "push", "push", "top", "pop", "empty"]], [[[], [1], [2], [], [], []]]):
            # /* Example
            #  *  Input
            #  *  ["MyStack", "push", "push", "top", "pop", "empty"]
            #  *  [[], [1], [2], [], [], []]
            #  *  Output
            #  *  [null, null, null, 2, 2, false]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "MyStack":
                    obj = MyStack()
                    displayStr.append(None)
                elif key == "push":
                    obj.push(value[0])
                    displayStr.append(None)
                elif key == "pop":
                    retVal = obj.pop()
                    displayStr.append(retVal)
                elif key == "top":
                    retVal = obj.top()
                    displayStr.append(retVal)
                if key == "empty":
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
