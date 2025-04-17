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
    def countPairs(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize-1):
            for j in range(i+1, numsSize):
                if (nums[i] == nums[j]) and ((i * j) % k == 0):
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[3, 1, 2, 2, 2, 1, 3], [1, 2, 3, 4]], [2, 1]):
            # /* Example
            #  *  Input: nums = [3,1,2,2,2,1,3], k = 2
            #  *  Output: 4
            #  *
            #  *  Input: nums = [1,2,3,4], k = 1
            #  *  Output: 0
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.countPairs(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
