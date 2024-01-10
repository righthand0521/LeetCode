import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from random import choice


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class RandomizedSet:
    def __init__(self):
        self.nums = []
        self.indices = {}

    def insert(self, val: int) -> bool:
        retVal = False

        if val in self.indices:
            return retVal
        self.indices[val] = len(self.nums)
        self.nums.append(val)
        retVal = True

        return retVal

    def remove(self, val: int) -> bool:
        retVal = False

        if val not in self.indices:
            return retVal
        id = self.indices[val]
        self.nums[id] = self.nums[-1]
        self.indices[self.nums[id]] = id
        self.nums.pop()
        del self.indices[val]
        retVal = True

        return retVal

    def getRandom(self) -> int:
        retVal = 0

        retVal = choice(self.nums)

        return retVal

# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["RandomizedSet", "insert", "remove", "insert",
                "getRandom", "remove", "insert", "getRandom"]],
                [[[], [1], [2], [2], [], [1], [2], []]]):
            # /* Example
            #  *  Input
            #  *  ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
            #  *  [[], [1], [2], [2], [], [1], [2], []]
            #  *  Output
            #  *  [null, true, false, true, 2, true, false, 2]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "RandomizedSet":
                    obj = RandomizedSet()
                    displayStr.append(None)
                elif key == "insert":
                    retVal = obj.insert(value[0])
                    displayStr.append(retVal)
                elif key == "remove":
                    retVal = obj.remove(value[0])
                    displayStr.append(retVal)
                elif key == "getRandom":
                    retVal = obj.getRandom()
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
