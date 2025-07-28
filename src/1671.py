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
    def lowerBound(self, lis: List[int], target: int) -> int:
        retVal = 0

        left = 0
        right = len(lis)
        while left < right:
            mid = left + (right - left) // 2
            if lis[mid] < target:
                left = mid + 1
            else:
                right = mid
        retVal = left

        return retVal

    def getLongestIncreasingSubsequenceLength(self, v: List[int]) -> List[int]:
        retVal = None

        vSize = len(v)
        retVal = [1] * vSize
        lis = [v[0]]
        for i in range(1, vSize):
            index = self.lowerBound(lis, v[i])
            if index == len(lis):
                lis.append(v[i])
            else:
                lis[index] = v[i]

            retVal[i] = len(lis)

        return retVal

    def minimumMountainRemovals(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        lisLength = self.getLongestIncreasingSubsequenceLength(nums)
        nums.reverse()
        ldsLength = self.getLongestIncreasingSubsequenceLength(nums)
        ldsLength.reverse()

        retVal = float("inf")
        for i in range(numsSize):
            if (lisLength[i] > 1) and (ldsLength[i] > 1):
                retVal = min(retVal, numsSize - lisLength[i] - ldsLength[i] + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 3, 1], [2, 1, 1, 5, 6, 2, 3, 1]]:
            # /* Example
            #  *  Input: nums = [1,3,1]
            #  *  Output: 0
            #  *
            #  *  Input: nums = [2,1,1,5,6,2,3,1]
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.minimumMountainRemovals(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
