import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


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
    def maxSum(self, nums: List[int]) -> int:
        retVal = 0

        positiveNumsSet = set([num for num in nums if num > 0])
        retVal = max(nums) if len(positiveNumsSet) == 0 else sum(positiveNumsSet)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 3, 4, 5], [1, 1, 0, 1, 1], [1, 2, -1, -2, 1, 0, -1]]:
            # /* Example
            #  *  Input: nums = [1,2,3,4,5]
            #  *  Output: 15
            #  *
            #  *  Input: nums = [1,1,0,1,1]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,2,-1,-2,1,0,-1]
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.maxSum(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
