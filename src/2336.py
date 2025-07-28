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


class SmallestInfiniteSet:
    def __init__(self):
        self.current = 1
        self.record = set()

    def popSmallest(self) -> int:
        retVal = 0

        if self.record:
            retVal = min(self.record)
            self.record.remove(retVal)
        else:
            self.current += 1
            retVal = self.current - 1

        return retVal

    def addBack(self, num: int) -> None:
        if self.current > num:
            self.record.add(num)

# Your SmallestInfiniteSet object will be instantiated and called as such:
# obj = SmallestInfiniteSet()
# param_1 = obj.popSmallest()
# obj.addBack(num)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, num in zip([["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest",
                                  "popSmallest", "addBack", "popSmallest", "popSmallest", "popSmallest"]],
                                [[None, 2, None, None, None, 1, None, None, None]]):
            # /* Example
            #  *  Input
            #  *  ["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest", "addBack", "popSmallest",
            #  * "popSmallest", "popSmallest"]
            #  *  [[], [2], [], [], [], [1], [], [], []]
            #  *  Output
            #  *  [null, null, 1, 2, 3, null, 1, 4, 5]
            #  */
            logging.info("%s", methods)
            logging.info("%s", num)

            displayStr = []
            obj = SmallestInfiniteSet()
            for p, q in zip(methods, num):
                if p == "SmallestInfiniteSet":
                    displayStr.append(None)
                elif p == "addBack":
                    obj.addBack(q)
                    displayStr.append(None)
                elif p == "popSmallest":
                    retVal = obj.popSmallest()
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
