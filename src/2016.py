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
    def maximumDifference(self, nums: List[int]) -> int:
        retVal = -1  # If no such i and j exists, return -1.

        numsSize = len(nums)

        minNum = nums[0]
        for i in range(1, numsSize):
            if nums[i] > minNum:
                retVal = max(retVal, nums[i] - minNum)
            else:
                minNum = nums[i]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[7, 1, 5, 4], [9, 4, 3, 2], [1, 5, 2, 10], [9, 4, 4]]:
            # /* Example
            #  *  Input: nums = [7,1,5,4]
            #  *  Output: 4
            #  *
            #  *  Input: nums = [9,4,3,2]
            #  *  Output: -1
            #  *
            #  *  Input: nums = [1,5,2,10]
            #  *  Output: 9
            #  *
            #  *  Input: nums = [9,4,4]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maximumDifference(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
