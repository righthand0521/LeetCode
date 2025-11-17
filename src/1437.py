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
    def kLengthApart(self, nums: List[int], k: int) -> bool:
        retVal = False

        numsSize = len(nums)
        previous = -1
        for i in range(numsSize):
            if nums[i] != 1:
                continue
            if (previous != -1) and (i - previous - 1 < k):
                return retVal
            previous = i
        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in [[[1, 0, 0, 0, 1, 0, 0, 1], 2], [[1, 0, 0, 1, 0, 1], 2]]:
            # /* Example:
            #  *  Input: nums = [1, 0, 0, 0, 1, 0, 0, 1], k = 2
            #  *  Output: true
            #  *
            #  *  Input: nums = [1, 0, 0, 1, 0, 1], k = 2
            #  *  Output: false
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.kLengthApart(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
