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
        retVal = -1  # If it is impossible to make all elements equal to k, return -1.

        hashTable = set()
        for x in nums:
            if x < k:
                return retVal
            elif x > k:
                hashTable.add(x)
        retVal = len(hashTable)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, k in zip([[5, 2, 5, 4, 5], [2, 1, 2], [9, 7, 5, 3]], [2, 2, 1]):
            # /* Example
            #  *  Input: nums = [5,2,5,4,5], k = 2
            #  *  Output: 2
            #  *
            #  *  Input: nums = [2,1,2], k = 2
            #  *  Output: -1
            #  *
            #  *  Input: nums = [9,7,5,3], k = 1
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
