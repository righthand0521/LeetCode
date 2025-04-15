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


class Solution:
    def __init__(self) -> None:
        self.a = None
        self.c = None

    def Discretization(self, nums: List[int]) -> None:
        self.a = nums.copy()
        self.a.sort()
        self.a = list(dict.fromkeys(self.a))

    def Update(self, pos: int) -> None:
        cSize = len(self.c)
        while pos < cSize:
            self.c[pos] += 1
            pos += (pos & (-pos))

    def Query(self, pos: int) -> int:
        retVal = 0

        while pos > 0:
            retVal += self.c[pos]
            pos -= (pos & (-pos))

        return retVal

    def getId(self, x: int) -> int:
        retVal = bisect_left(self.a, x) + 1

        return retVal

    def countSmaller(self, nums: List[int]) -> List[int]:
        retVal = None

        numSize = len(nums)

        self.a = [0] * numSize
        self.Discretization(nums)

        self.c = [0] * (numSize + 5)
        retVal = [0] * numSize
        for i in range(numSize - 1, -1, -1):
            id = self.getId(nums[i])
            retVal[i] = self.Query(id - 1)
            self.Update(id)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[5, 2, 6, 1], [-1], [-1, -1]]:
            # /* Example
            #  *  Input: nums = [5,2,6,1]
            #  *  Output: [2,1,1,0]
            #  *
            #  *  Input: nums = [-1]
            #  *  Output: [0]
            #  *
            #  *  Input: nums = [-1,-1]
            #  *  Output: [0,0]
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.countSmaller(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
