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


class Solution:
    def getCost(self, base: int, nums: List[int], cost: List[int]) -> int:
        retVal = 0

        retVal = sum(abs(base - num) * c for num, c in zip(nums, cost))

        return retVal

    def minCost(self, nums: List[int], cost: List[int]) -> int:
        retVal = 0

        retVal = self.getCost(nums[0], nums, cost)
        left = min(nums)
        right = max(nums)
        while left < right:
            middle = (left + right) // 2

            costLeft = self.getCost(middle, nums, cost)
            costRight = self.getCost((middle + 1), nums, cost)
            retVal = min(costLeft, costRight)

            if costLeft > costRight:
                left = middle + 1
            else:
                right = middle

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, cost in zip([[1, 3, 5, 2], [2, 2, 2, 2, 2]], [[2, 3, 1, 14], [4, 2, 8, 1, 3]]):
            # /* Example
            #  *  Input: nums = [1,3,5,2], cost = [2,3,1,14]
            #  *  Output: 8
            #  *
            #  *  Input: nums = [2,2,2,2,2], cost = [4,2,8,1,3]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, cost = %s", nums, cost)

            retVal = pSolution.minCost(nums, cost)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
