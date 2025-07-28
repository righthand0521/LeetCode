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


class MyHashSet:
    def __init__(self):
        self.mod = 1000
        self.bucket = [[] for _ in range(self.mod)]

    def add(self, key: int) -> None:
        idx = key % self.mod
        if key not in self.bucket[idx]:
            self.bucket[idx].append(key)

    def remove(self, key: int) -> None:
        idx = key % self.mod
        if key in self.bucket[idx]:
            self.bucket[idx].remove(key)

    def contains(self, key: int) -> bool:
        retVal = False

        idx = key % self.mod
        retVal = key in self.bucket[idx]

        return retVal

# Your MyHashSet object will be instantiated and called as such:
# obj = MyHashSet()
# obj.add(key)
# obj.remove(key)
# param_3 = obj.contains(key)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip(
            [["MyHashSet", "add", "add", "contains", "contains",
                "add", "contains", "remove", "contains"]],
                [[[], [1], [2], [1], [3], [2], [2], [2], [2]]]):
            # /* Example
            #  *  Input
            #  *  ["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
            #  *  [[], [1], [2], [1], [3], [2], [2], [2], [2]]
            #  *  Output
            #  *  [null, null, null, true, false, null, true, null, false]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "MyHashSet":
                    obj = MyHashSet()
                    displayStr.append(None)
                elif key == "add":
                    obj.add(value[0])
                    displayStr.append(None)
                elif key == "remove":
                    obj.remove(value[0])
                    displayStr.append(None)
                elif key == "contains":
                    retVal = obj.contains(value[0])
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
