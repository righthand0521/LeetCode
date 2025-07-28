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


class MyHashMap:
    def __init__(self):
        # 0 <= key, value <= 10^6
        self.mod = 1000
        self.map = [[-1] * self.mod for _ in range(self.mod + 1)]

    def put(self, key: int, value: int) -> None:
        row = key // self.mod
        col = key % self.mod
        self.map[row][col] = value

    def get(self, key: int) -> int:
        retVal = -1

        row = key // self.mod
        col = key % self.mod
        retVal = self.map[row][col]

        return retVal

    def remove(self, key: int) -> None:
        row = key // self.mod
        col = key % self.mod
        self.map[row][col] = -1

# Your MyHashMap object will be instantiated and called as such:
# obj = MyHashMap()
# obj.put(key,value)
# param_2 = obj.get(key)
# obj.remove(key)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]],
                                [[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]]):
            # /* Example
            #  *  Input
            #  *  ["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
            #  *  [[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
            #  *  Output
            #  *  [null, null, null, 1, -1, null, 1, null, -1]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "MyHashMap":
                    obj = MyHashMap()
                    displayStr.append(None)
                elif key == "put":
                    obj.put(value[0], value[1])
                    displayStr.append(None)
                elif key == "get":
                    retVal = obj.get(value[0])
                    displayStr.append(retVal)
                elif key == "remove":
                    obj.remove(value[0])
                    displayStr.append(None)
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
