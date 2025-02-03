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
    def longestMonotonicSubarray(self, nums: List[int]) -> int:
        retVal = 1

        numsSize = len(nums)

        increasing = 1
        decreasing = 1
        for i in range(1, numsSize):
            if (nums[i-1] < nums[i]):
                increasing += 1
                decreasing = 1
            elif (nums[i-1] > nums[i]):
                decreasing += 1
                increasing = 1
            else:
                increasing = 1
                decreasing = 1
            retVal = max(retVal, max(increasing, decreasing))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 4, 3, 3, 2], [3, 3, 3, 3], [3, 2, 1]]:
            # /* Example
            #  *  Input: nums = [1,4,3,3,2]
            #  *  Output: 2
            #  *
            #  *  Input: nums = [3,3,3,3]
            #  *  Output: 1
            #  *
            #  *  Input: nums = [3,2,1]
            #  *  Output: 3
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.longestMonotonicSubarray(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
