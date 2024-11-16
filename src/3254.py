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
    def resultsArray(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        if k == 1:
            retVal = nums
            return retVal

        numsSize = len(nums)
        retVal = [-1] * (numsSize - k + 1)
        consecutiveCount = 1
        for i in range(numsSize - 1):
            if nums[i] + 1 == nums[i + 1]:
                consecutiveCount += 1
            else:
                consecutiveCount = 1

            if consecutiveCount >= k:
                retVal[i - k + 2] = nums[i + 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[1, 2, 3, 4, 3, 2, 5], [2, 2, 2, 2, 2], [3, 2, 3, 2, 3, 2]], [3, 4, 2]):
            # /* Example
            #  *  Input: nums = [1,2,3,4,3,2,5], k = 3
            #  *  Output: [3,4,-1,-1,-1]
            #  *
            #  *  Input: nums = [2,2,2,2,2], k = 4
            #  *  Output: [-1,-1]
            #  *
            #  *  Input: nums = [3,2,3,2,3,2], k = 2
            #  *  Output: [-1,3,-1,3,-1]
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.resultsArray(nums, k)
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
