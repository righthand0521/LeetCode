import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from random import choice
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
    def minOperations(self, nums: List[int], k: int) -> int:
        retVal = 0

        heapify(nums)
        while nums[0] < k:
            x = heappop(nums)
            y = heappop(nums)
            heappush(nums, min(x, y) * 2 + max(x, y))
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[2, 11, 10, 1, 3], [1, 1, 2, 4, 9]], [10, 20]):
            # /* Example
            #  *  Input: nums = [2,11,10,1,3], k = 10
            #  *  Output: 2
            #  *
            #  *  Input: nums = [1,1,2,4,9], k = 20
            #  *  Output: 4
            #  */
            logging.info("Input: nums = %s, k = %s", nums, k)

            retVal = pSolution.minOperations(nums, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
