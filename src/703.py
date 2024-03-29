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


class KthLargest:
    def __init__(self, k: int, nums: List[int]):
        self.k = k
        self.nums = nums
        heapify(self.nums)
        while len(self.nums) > k:
            heappop(self.nums)

    def add(self, val: int) -> int:
        retVal = 0

        heappush(self.nums, val)
        if len(self.nums) > self.k:
            heappop(self.nums)
        retVal = self.nums[0]

        return retVal

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
        for methods, num in zip([["KthLargest", "add", "add", "add", "add", "add"]], [[None, 3, 5, 10, 9, 4]]):
            # /* Example
            #  *  Input
            #  *  ["KthLargest", "add", "add", "add", "add", "add"]
            #  *  [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
            #  *  Output
            #  *  [null, 4, 5, 5, 8, 8]
            #  */
            logging.info("%s", methods)
            displayStr = []
            for p in num:
                if p == None:
                    displayStr.append('[[3, [4, 5, 8, 2]]')
                else:
                    displayStr.append(p)
            logging.info("%s", displayStr)

            displayStr = []
            obj = KthLargest(3, [4, 5, 8, 2])
            for p, q in zip(methods, num):
                if p == "KthLargest":
                    displayStr.append(None)
                elif p == "add":
                    retVal = obj.add(q)
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
