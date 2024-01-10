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
    def isMonotonic(self, nums: List[int]) -> bool:
        retVal = True

        numsSize = len(nums)
        if numsSize == 1:   # 1 <= nums.length <= 10^5
            return retVal

        previous = 0
        for i in range(1, numsSize):
            if nums[i] == nums[i-1]:
                continue
            elif nums[i] > nums[i-1]:
                diff = 1
            elif nums[i] < nums[i-1]:
                diff = -1

            if (previous != 0):
                if previous != diff:
                    retVal = False
                    break
            previous = diff

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[1, 2, 2, 3], [6, 5, 4, 4], [1, 3, 2]]:
            # /* Example
            #  *  Input: nums = [1,2,2,3]
            #  *  Output: true
            #  *
            #  *  Input: nums = [6,5,4,4]
            #  *  Output: true
            #  *
            #  *  Input: nums = [1,3,2]
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.isMonotonic(nums)
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
