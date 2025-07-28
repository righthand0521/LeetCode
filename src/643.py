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
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        retVal = 0

        numsSize = len(nums)

        sum = 0
        for i in range(k):
            sum += nums[i]
        maxValue = sum

        for i in range(k, numsSize):
            sum += (nums[i] - nums[i - k])
            maxValue = max(maxValue, sum)
        retVal = maxValue / k

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 12, -5, -6, 50, 3], [5]], [4, 1]):
            # /* Example
            #  *  Input: nums = [1,12,-5,-6,50,3], k = 4
            #  *  Output: 12.75000
            #  *
            #  *  Input: nums = [5], k = 1
            #  *  Output: 5.00000
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.findMaxAverage(nums, k)
            logging.info("Output: %.5f", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
