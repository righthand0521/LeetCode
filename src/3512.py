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
    def minOperations(self, nums: List[int], k: int) -> int:
        retVal = 0

        retVal = sum(nums) % k

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in [[3, 9, 7], 5], [[4, 1, 3], 4], [[3, 2], 6]:
            # /* Example
            #  *  Input: nums = [3,9,7], k = 5
            #  *  Output: 4
            #  *
            #  *  Input: nums = [4,1,3], k = 4
            #  *  Output: 0
            #  *
            #  *  Input: nums = [3,2], k = 6
            #  *  Output: 5
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
