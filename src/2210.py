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
    def countHillValley(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        # /* Example: Input: nums = [2,4,1,1,6,5]
        #  *  2   4   1   1   6   5
        #  *    2  -3   0   5  -1
        #  */
        diff = 0
        for i in range(1, numsSize):
            if nums[i] > nums[i-1]:
                if diff == -1:
                    retVal += 1
                diff = 1
            elif nums[i] < nums[i-1]:
                if diff == 1:
                    retVal += 1
                diff = -1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[2, 4, 1, 1, 6, 5], [6, 6, 5, 5, 4, 1]]:
            # /* Example
            #  *  Input: nums = [2,4,1,1,6,5]
            #  *  Output: 3
            #  *
            #  *  Input: nums = [6,6,5,5,4,1]
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.countHillValley(nums)
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
