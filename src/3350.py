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
    def maxIncreasingSubarrays(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        current = 1
        previous = 0
        for i in range(1, numsSize):
            if nums[i] > nums[i - 1]:
                current += 1
            else:
                previous = current
                current = 1
            retVal = max(retVal, min(previous, current))
            retVal = max(retVal, current // 2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 5, 7, 8, 9, 2, 3, 4, 3, 1], [1, 2, 3, 4, 4, 4, 4, 5, 6, 7]]:
            # /* Example
            #  *  Input: nums = [2,5,7,8,9,2,3,4,3,1]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [1,2,3,4,4,4,4,5,6,7]
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxIncreasingSubarrays(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
