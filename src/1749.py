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
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        retVal = 0

        prefixSum = 0
        minPrefixSum = 0
        maxPrefixSum = 0
        for num in nums:
            prefixSum += num
            minPrefixSum = min(minPrefixSum, prefixSum)
            maxPrefixSum = max(maxPrefixSum, prefixSum)
        retVal = maxPrefixSum - minPrefixSum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, -3, 2, 3, -4], [2, -5, 1, -4, 3, -2]]:
            # /* Example
            #  *  Input: nums = [1,-3,2,3,-4]
            #  *  Output: 5
            #  *
            #  *  Input: nums = [2,-5,1,-4,3,-2]
            #  *  Output: 8
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxAbsoluteSum(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
