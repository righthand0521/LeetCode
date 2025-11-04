import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from sortedcontainers import SortedList


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class Helper:
    def __init__(self, x: int) -> None:
        self.x = x
        self.result = 0
        self.large = SortedList()
        self.small = SortedList()
        self.occ = defaultdict(int)

    def insert(self, num: int) -> None:
        if self.occ[num] > 0:
            self.internal_remove((self.occ[num], num))
        self.occ[num] += 1
        self.internal_insert((self.occ[num], num))

    def remove(self, num: int) -> None:
        self.internal_remove((self.occ[num], num))
        self.occ[num] -= 1
        if self.occ[num] > 0:
            self.internal_insert((self.occ[num], num))

    def get(self) -> int:
        retVal = self.result

        return retVal

    def internal_insert(self, p: tuple) -> None:
        largeSize = len(self.large)
        if (largeSize < self.x) or (p > self.large[0]):
            self.result += (p[0] * p[1])
            self.large.add(p)
            largeSize = len(self.large)
            if largeSize > self.x:
                to_remove = self.large[0]
                self.result -= (to_remove[0] * to_remove[1])
                self.large.remove(to_remove)
                self.small.add(to_remove)
        else:
            self.small.add(p)

    def internal_remove(self, p: tuple) -> None:
        if p >= self.large[0]:
            self.result -= (p[0] * p[1])
            self.large.remove(p)
            if self.small:
                to_add = self.small[-1]
                self.result += (to_add[0] * to_add[1])
                self.small.remove(to_add)
                self.large.add(to_add)
        else:
            self.small.remove(p)


class Solution:
    def findXSum(self, nums: List[int], k: int, x: int) -> List[int]:
        retVal = []

        helper = Helper(x)

        numsSize = len(nums)
        for i in range(numsSize):
            helper.insert(nums[i])
            if i >= k:
                helper.remove(nums[i - k])
            if i >= k - 1:
                retVal.append(helper.get())

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k, x in [[[1, 1, 2, 2, 3, 4, 2, 3], 6, 2], [[3, 8, 7, 8, 7, 5], 2, 2]]:
            # /* Example
            #  *  Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
            #  *  Output: [6,10,12]
            #  *
            #  *  Input: nums = [3,8,7,8,7,5], k = 2, x = 2
            #  *  Output: [11,15,15,15,12]
            #  */
            logging.info("Input: nums = %s, k = %s, x = %s", nums, k, x)

            retVal = pSolution.findXSum(nums, k, x)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
