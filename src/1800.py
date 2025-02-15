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
    def maxAscendingSum(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        sum = nums[0]
        for i in range(1, numsSize):
            if (nums[i-1] >= nums[i]):
                retVal = max(retVal, sum)
                sum = 0
            sum += nums[i]
        retVal = max(retVal, sum)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[10, 20, 30, 5, 10, 50], [10, 20, 30, 40, 50], [12, 17, 15, 13, 10, 11, 12]]:
            # /* Example
            #  *  Input: nums = [10,20,30,5,10,50]
            #  *  Output: 65
            #  *
            #  *  Input: nums = [10,20,30,40,50]
            #  *  Output: 150
            #  *
            #  *  Input: nums = [12,17,15,13,10,11,12]
            #  *  Output: 33
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxAscendingSum(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
