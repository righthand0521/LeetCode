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
    def waysToSplitArray(self, nums: list[int]) -> int:
        retVal = 0

        leftSum = 0
        rightSum = sum(nums)

        numsSize = len(nums)
        for i in range(numsSize - 1):
            leftSum += nums[i]
            rightSum -= nums[i]
            if leftSum >= rightSum:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[10, 4, -8, 7], [2, 3, 1, 0]]:
            # /* Example
            #  *  Input: nums = [10,4,-8,7]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [2,3,1,0]
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.waysToSplitArray(nums)
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
