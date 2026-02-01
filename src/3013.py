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


class Container:
    def __init__(self, k: int):
        self.k = k
        self.st1 = SortedList()
        self.st2 = SortedList()
        self.sm = 0

    def adjust(self) -> None:
        while True:
            st1Size = len(self.st1)
            st2Size = len(self.st2)
            if st1Size >= self.k:
                break
            elif st2Size <= 0:
                break
            x = self.st2[0]
            self.st1.add(x)
            self.st2.remove(x)
            self.sm += x

        while True:
            st1Size = len(self.st1)
            if st1Size <= self.k:
                break
            x = self.st1[-1]
            self.st2.add(x)
            self.st1.remove(x)
            self.sm -= x

    def add(self, x: int) -> None:
        st2Size = len(self.st2)
        if (st2Size > 0) and (x >= self.st2[0]):
            self.st2.add(x)
        else:
            self.st1.add(x)
            self.sm += x
        self.adjust()

    def erase(self, x: int) -> None:
        if x in self.st1:
            self.st1.remove(x)
            self.sm -= x
        elif x in self.st2:
            self.st2.remove(x)
        self.adjust()

    def sum(self) -> int:
        retVal = self.sm

        return retVal


class Solution:
    def minimumCost(self, nums: List[int], k: int, dist: int) -> int:
        retVal = 0

        numsSize = len(nums)

        cnt = Container(k - 2)
        for i in range(1, k - 1):
            cnt.add(nums[i])

        retVal = cnt.sum() + nums[k - 1]
        for i in range(k, numsSize):
            j = i - dist - 1
            if j > 0:
                cnt.erase(nums[j])
            cnt.add(nums[i - 1])
            retVal = min(retVal, cnt.sum() + nums[i])
        retVal += nums[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k, dist in [[[1, 3, 2, 6, 4, 2], 3, 3], [[10, 1, 2, 2, 2, 1], 4, 3], [[10, 8, 18, 9], 3, 1]]:
            # /* Example
            #  *  Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
            #  *  Output: 5
            #  *
            #  *  Input: nums = [10,1,2,2,2,1], k = 4, dist = 3
            #  *  Output: 15
            #  *
            #  *  Input: nums = [10,8,18,9], k = 3, dist = 1
            #  *  Output: 36
            #  */
            logging.info("Input: nums = %s, k = %s, dist = %s", nums, k, dist)

            retVal = pSolution.minimumCost(nums, k, dist)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
