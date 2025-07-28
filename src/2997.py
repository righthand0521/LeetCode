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
    def minOperations(self, nums: List[int], k: int) -> int:
        retVal = 0

        xorValue = 0
        for num in nums:
            xorValue ^= num
        xorValue ^= k
        retVal = xorValue.bit_count()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[2, 1, 3, 4], [2, 0, 2, 0]], [1, 0]):
            # /* Example
            #  *  Input: nums = [2,1,3,4], k = 1
            #  *  Output: 2
            #  *
            #  *  Input: nums = [2,0,2,0], k = 0
            #  *  Output: 0
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
