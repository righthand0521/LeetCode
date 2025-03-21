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
    def longestNiceSubarray(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        niceCheck = 0
        head = 0
        tail = 0
        while (tail < numsSize):
            while ((niceCheck & nums[tail]) != 0):
                niceCheck ^= nums[head]
                head += 1
            retVal = max(retVal, tail - head + 1)

            niceCheck |= nums[tail]
            tail += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 3, 8, 48, 10], [3, 1, 5, 11, 13]]:
            # /* Example
            #  *  Input: nums = [1,3,8,48,10]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [3,1,5,11,13]
            #  *  Output: 1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.longestNiceSubarray(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
