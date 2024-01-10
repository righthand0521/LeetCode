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


class MountainArray:
    def __init__(self, arr) -> None:
        self.arr = arr

    def get(self, index: int) -> int:
        retVal = self.arr[index]

        return retVal

    def length(self) -> int:
        retVal = len(self.arr)

        return retVal

# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
# class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:


class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        retVal = -1

        arrSize = mountain_arr.length()

        # Find the index of the peak element
        left = 0
        right = arrSize - 1
        while left < right:
            middle = left + (right - left) // 2
            if mountain_arr.get(middle) < mountain_arr.get(middle+1):
                left = middle + 1
            else:
                right = middle
        peak = left

        # Search in the strictly increasing part of the array. If found, will be returned in the loop itself.
        left = 0
        right = peak
        while left <= right:
            middle = (left + right) // 2
            value = mountain_arr.get(middle)
            if value == target:
                retVal = middle
                return retVal
            elif value < target:
                left = middle + 1
            else:
                right = middle - 1

        # Search in the strictly decreasing part of the array. If found, will be returned in the loop itself.
        left = peak + 1
        right = arrSize - 1
        while left <= right:
            middle = (left + right) // 2
            value = mountain_arr.get(middle)
            if value == target:
                retVal = middle
                return retVal
            elif value > target:
                left = middle + 1
            else:
                right = middle - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, target in zip([[1, 2, 3, 4, 5, 3, 1], [0, 1, 2, 4, 2, 1], [0, 5, 3, 1]], [3, 3, 1]):
            # /* Example
            #  *  Input: array = [1,2,3,4,5,3,1], target = 3
            #  *  Output: 2
            #  *
            #  *  Input: array = [0,1,2,4,2,1], target = 3
            #  *  Output: -1
            #  *
            #  *  Input: array = [0,5,3,1], target = 1
            #  *  Output: 3
            #  */
            logging.info("Input: arr = %s, target = %s", arr, target)

            retVal = pSolution.findInMountainArray(target, MountainArray(arr))
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
