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
    def findMaxK(self, nums: List[int]) -> int:
        retVal = -1

        nums.sort()

        left = 0
        right = len(nums) - 1
        while left < right:
            if (-nums[left]) == nums[right]:
                retVal = nums[right]
                break
            elif (-nums[left]) > nums[right]:
                left += 1
            elif (-nums[left]) < nums[right]:
                right -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[-1, 2, -3, 3], [-1, 10, 6, 7, -7, 1], [-10, 8, 6, 7, -2, -3]]:
            # /* Example
            #  *  Input: nums = [-1,2,-3,3]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [-1,10,6,7,-7,1]
            #  *  Output: 7
            #  *
            #  *  Input: nums = [-10,8,6,7,-2,-3]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.findMaxK(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
