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
    def check(self, nums: List[int]) -> bool:
        retVal = True

        numsSize = len(nums)
        if numsSize <= 1:
            return retVal

        inversionCount = 0
        for i in range(1, numsSize):
            if nums[i - 1] > nums[i]:
                inversionCount += 1
        if nums[numsSize - 1] > nums[0]:
            inversionCount += 1
        retVal = (inversionCount <= 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums in [[3, 4, 5, 1, 2],  [2, 1, 3, 4], [1, 2, 3], [2, 4, 1, 3], [1, 3, 2]]:
            # /* Example
            #  *  Input: nums = [3,4,5,1,2]
            #  *  Output: true
            #  *
            #  *  Input: nums = [2,1,3,4]
            #  *  Output: false
            #  *
            #  *  Input: nums = [1,2,3]
            #  *  Output: true
            #  *
            #  *  Input: nums = [2,4,1,3]
            #  *  Output: false
            #  *
            #  *  Input: nums = [1,3,2]
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s", nums)

            retVal = pSolution.check(nums)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
