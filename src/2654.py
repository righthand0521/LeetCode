import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from math import gcd


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
    def minOperations(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        numberOfOne = 0
        greatestCommonDivisor = 0
        for num in nums:
            if num == 1:
                numberOfOne += 1
            greatestCommonDivisor = gcd(greatestCommonDivisor, num)
        if numberOfOne > 0:
            retVal = numsSize - numberOfOne
            return retVal
        elif greatestCommonDivisor > 1:
            return retVal

        minNumsSize = numsSize
        for i in range(numsSize):
            greatestCommonDivisor = 0
            for j in range(i, numsSize):
                greatestCommonDivisor = gcd(greatestCommonDivisor, nums[j])
                if greatestCommonDivisor == 1:
                    minNumsSize = min(minNumsSize, j - i + 1)
                    break
        retVal = minNumsSize + numsSize - 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 6, 3, 4], [2, 10, 6, 14]]:
            # /* Example
            #  *  Input: nums = [2,6,3,4]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [2,10,6,14]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minOperations(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
