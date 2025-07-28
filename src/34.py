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
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        retVal = [-1, -1]

        numsSize = len(nums)
        if numsSize == 0:
            return retVal

        left = 0
        right = numsSize - 1
        while left < right:
            middle = left + (right - left) // 2
            if nums[middle] >= target:
                right = middle
            else:
                left = middle + 1
        if nums[right] != target:
            return retVal
        retVal[0] = right

        left = 0
        right = numsSize - 1
        while left < right:
            middle = right - (right - left) // 2
            if nums[middle] <= target:
                left = middle
            else:
                right = middle - 1
        if nums[right] != target:
            retVal[0] = -1
            return retVal
        retVal[1] = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, target in [[[5, 7, 7, 8, 8, 10], 8], [[5, 7, 7, 8, 8, 10], 6], [[], 0], [[1], 1], [[2, 2], 2]]:
            # /* Example
            #  *  Input: nums = [5,7,7,8,8,10], target = 8
            #  *  Output: [3,4]
            #  *
            #  *  Input: nums = [5,7,7,8,8,10], target = 6
            #  *  Output: [-1,-1]
            #  *
            #  *  Input: nums = [], target = 0
            #  *  Output: [-1,-1]
            #  *
            #  *  Input: nums = [1], target = 1
            #  *  Output: [0,0]
            #  *
            #  *  Input: nums = [2,2], target = 2
            #  *  Output: [0,1]
            #  */
            logging.info("Input: nums = %s, target = %s", nums, target)

            retVal = pSolution.searchRange(nums, target)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
