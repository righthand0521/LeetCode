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
    # Helper function to calculate the minimum swaps required to group all value together
    def minSwapsHelper(self, nums: List[int], value: int) -> int:
        retVal = 0

        numsSize = len(nums)

        # Count the total number of value in the array
        totalValCount = 0
        for i in range(numsSize - 1, -1, -1):
            if nums[i] == value:
                totalValCount += 1
        # If there is no value or the array is full of value, no swaps are needed
        if (totalValCount == 0) or (totalValCount == numsSize):
            return retVal

        start = 0
        end = 0
        currentValInWindow = 0
        maxValInWindow = 0

        # Initial window setup: count the number of value in the first window of size `totalValCount`
        while end < totalValCount:
            if nums[end] == value:
                currentValInWindow += 1
            end += 1
        maxValInWindow = max(maxValInWindow, currentValInWindow)

        # Slide the window across the array to find the maximum number of value in any window
        while end < numsSize:
            if nums[start] == value:
                currentValInWindow -= 1
            start += 1

            if nums[end] == value:
                currentValInWindow += 1
            end += 1

            maxValInWindow = max(maxValInWindow, currentValInWindow)

        # Minimum swaps are the total value minus the maximum found in any window
        retVal = totalValCount - maxValInWindow

        return retVal

    def minSwaps(self, nums: List[int]) -> int:
        retVal = 0

        # Calculate the minimum swaps needed to group all 1s or all 0s together
        op0 = self.minSwapsHelper(nums, 0)  # Grouping all 0s together
        op1 = self.minSwapsHelper(nums, 1)  # Grouping all 1s together
        retVal = min(op0, op1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[0, 1, 0, 1, 1, 0, 0], [0, 1, 1, 1, 0, 0, 1, 1, 0], [1, 1, 0, 0, 1]]:
            # /* Example
            #  *  Input: nums = [0,1,0,1,1,0,0]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [0,1,1,1,0,0,1,1,0]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,1,0,0,1]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minSwaps(nums)
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
