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
    def updateBitCounts(self, bitCounts: list, number: int, delta: int) -> None:
        for bitPosition in range(32):
            if number & (1 << bitPosition):
                bitCounts[bitPosition] += delta

    def convertBitCountsToNumber(self, bitCounts: list) -> int:
        retVal = 0

        for bitPosition in range(32):
            if bitCounts[bitPosition]:
                retVal |= (1 << bitPosition)

        return retVal

    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        retVal = -1

        numsSize = len(nums)
        windowStart = 0
        bitCounts = [0] * 32
        minLength = float("inf")
        for windowEnd in range(numsSize):
            self.updateBitCounts(bitCounts, nums[windowEnd], 1)

            while (windowStart <= windowEnd) and (self.convertBitCountsToNumber(bitCounts) >= k):
                minLength = min(minLength, windowEnd - windowStart + 1)
                self.updateBitCounts(bitCounts, nums[windowStart], -1)
                windowStart += 1

        if minLength != float("inf"):
            retVal = minLength

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 3], [2, 1, 8], [1, 2]], [2, 10, 0]):
            # /* Example
            #  *  Input: nums = [1,2,3], k = 2
            #  *  Output: 1
            #  *
            #  *  Input: nums = [2,1,8], k = 10
            #  *  Output: 3
            #  *
            #  *  Input: nums = [1,2], k = 0
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.minimumSubarrayLength(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
