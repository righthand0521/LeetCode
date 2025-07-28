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
    def minPatches(self, nums: List[int], n: int) -> int:
        retVal = 0

        numsSize = len(nums)
        index = 0
        x = 1
        while x <= n:
            if (index < numsSize) and (nums[index] <= x):
                x += nums[index]
                index += 1
            else:
                x <<= 1
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, n in zip([[1, 3], [1, 5, 10], [1, 2, 2]], [6, 20, 5]):
            # /* Example
            #  *  Input: nums = [1,3], n = 6
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,5,10], n = 20
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,2,2], n = 5
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, n = %s", nums, n)

            retVal = pSolution.minPatches(nums, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
