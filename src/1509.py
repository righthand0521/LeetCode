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
    def minDifference(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize <= 4:  # If the array has 4 or fewer elements, return 0
            return retVal

        nums.sort()
        minDiff = float("inf")

        # Four scenarios to compute the minimum difference
        for left in range(4):
            right = numsSize - 4 + left
            minDiff = min(minDiff, nums[right] - nums[left])
        retVal = minDiff

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[5, 3, 2, 4], [1, 5, 0, 10, 14], [3, 100, 20]]:
            # /* Example
            #  *  Input: nums = [5,3,2,4]
            #  *  Output: 0
            #  *
            #  *  Input: nums = [1,5,0,10,14]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [3,100,20]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minDifference(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
