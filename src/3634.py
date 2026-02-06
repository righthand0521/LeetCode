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
    def minRemoval(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        nums.sort()

        retVal = numsSize
        right = 0
        for left in range(numsSize):
            while (right < numsSize) and (nums[right] <= nums[left] * k):
                right += 1
            retVal = min(retVal, numsSize - (right - left))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in [[[2, 1, 5], 2], [[1, 6, 2, 9], 3], [[4, 6], 2]]:
            # /* Example
            #  *  Input: nums = [2,1,5], k = 2
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,6,2,9], k = 3
            #  *  Output: 2
            #  *
            #  *  Input: nums = [4,6], k = 2
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.minRemoval(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
