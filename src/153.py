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
    def findMin(self, nums: List[int]) -> int:
        retVal = 0

        left = 0
        right = len(nums) - 1
        while left < right:
            middle = left + (right - left) // 2
            if nums[middle] < nums[right]:
                right = middle
            else:
                left = middle + 1
        retVal = nums[left]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 4, 5, 1, 2], [4, 5, 6, 7, 0, 1, 2], [11, 13, 15, 17], [2, 1], [2, 3, 1]]:
            # /* Example 1:
            #  *  Input: nums = [3,4,5,1,2]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [4,5,6,7,0,1,2]
            #  *  Output: 0
            #  *
            #  *  Input: nums = [11,13,15,17]
            #  *  Output: 11
            #  *
            #  *  Input: nums = [2,1]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [2,3,1]
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.findMin(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
