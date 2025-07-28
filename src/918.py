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
    def maxSubarraySumCircular(self, nums: List[int]) -> int:
        retVal = 0

        # /* Kadane’s Algorithm: https://en.wikipedia.org/wiki/Maximum_subarray_problem
        #  *  1. Maximum Subarray is not Circular: maxSum
        #  *  2. Maximum Subarray is Circular: sum - minSum
        #  */
        curMax = 0
        sumMax = nums[0]
        curMin = 0
        sumMin = nums[0]
        sumTotal = 0
        for num in nums:
            curMax = max(curMax, 0) + num
            sumMax = max(sumMax, curMax)
            curMin = min(curMin, 0) + num
            sumMin = min(sumMin, curMin)
            sumTotal += num
        if sumTotal == sumMin:
            retVal = sumMax
        else:
            retVal = max(sumMax, sumTotal - sumMin)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, -2, 3, -2], [5, -3, 5], [-3, -2, -3]]:
            # /* Example
            #  *  Input: nums = [1,-2,3,-2]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [5,-3,5]
            #  *  Output: 10
            #  *
            #  *  Input: nums = [-3,-2,-3]
            #  *  Output: -2
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxSubarraySumCircular(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
