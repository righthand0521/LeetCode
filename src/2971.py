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
    def largestPerimeter(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        nums.sort()
        sum = nums[0] + nums[1]
        for i in range(2, numsSize):
            if sum > nums[i]:
                retVal = sum + nums[i]
            sum += nums[i]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[5, 5, 5], [1, 12, 1, 2, 5, 50, 3], [5, 5, 50]]:
            # /* Example
            #  *  Input: nums = [5,5,5]
            #  *  Output: 15
            #  *
            #  *  Input: nums = [1,12,1,2,5,50,3]
            #  *  Output: 12
            #  *
            #  *  Input: nums = [5,5,50]
            #  *  Output: -1
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.largestPerimeter(nums)
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
