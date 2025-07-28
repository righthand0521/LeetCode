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
    def lowerBound(self, nums: List[int], value: int) -> int:
        retVal = 0

        left = 0
        right = len(nums) - 1
        while left < right:
            sum = nums[left] + nums[right]

            # If sum is less than value, add the size of window to result and move to the next index.
            # Otherwise, shift the right pointer backwards, until we get a valid window.
            if sum < value:
                retVal += (right - left)
                left += 1
            else:
                right -= 1

        return retVal

    def countFairPairs(self, nums: List[int], lower: int, upper: int) -> int:
        retVal = 0

        nums.sort()
        retVal = self.lowerBound(nums, upper + 1) - self.lowerBound(nums, lower)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, lower, upper in zip([[0, 1, 7, 4, 4, 5], [1, 7, 9, 2, 5]], [3, 11], [6, 11]):
            # /* Example
            #  *  Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
            #  *  Output: 6
            #  *
            #  *  Input: nums = [1,7,9,2,5], lower = 11, upper = 11
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s, lower = %s, upper = %s", nums, lower, upper)

            retVal = pSolution.countFairPairs(nums, lower, upper)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
