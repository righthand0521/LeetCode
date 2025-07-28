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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def rangeSum(self, nums: List[int], n: int, left: int, right: int) -> int:
        retVal = 0

        numsSize = len(nums)

        numsSum = []
        for start in range(numsSize):
            sum = 0
            for idx in range(start, numsSize):
                sum += nums[idx]
                numsSum.append(sum)
        numsSum.sort()

        for idx in range(left-1, right):
            retVal += numsSum[idx]
            retVal %= self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, n, left, right in zip([[1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4]], [4, 4, 4], [1, 3, 1], [5, 4, 10]):
            # /* Example
            #  *  Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
            #  *  Output: 13
            #  *
            #  *  Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
            #  *  Output: 6
            #  *
            #  *  Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
            #  *  Output: 50
            #  */
            logging.info("Input: nums = %s, n = %s, left= %s, right = %s", nums, n, left, right)

            retVal = pSolution.rangeSum(nums, n, left, right)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
