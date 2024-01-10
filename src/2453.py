import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import inf


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
    def destroyTargets(self, nums: List[int], space: int) -> int:
        retVal = float('inf')

        count = defaultdict(int)
        for num in nums:
            count[num % space] += 1
        maxTarget = max(count.values())

        for num in nums:
            if count[num % space] == maxTarget:
                retVal = min(retVal, num)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, space in zip([[3, 7, 8, 1, 1, 5], [1, 3, 5, 2, 4, 6], [6, 2, 5]], [2, 2, 100]):
            # /* Example
            #  *  Input: nums = [3,7,8,1,1,5], space = 2
            #  *  Output: 1
            #  *
            #  *  Input: nums = [1,3,5,2,4,6], space = 2
            #  *  Output: 1
            #  *
            #  *  Input: nums = [6,2,5], space = 100
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, space = %s", nums, space)

            retVal = pSolution.destroyTargets(nums, space)
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
