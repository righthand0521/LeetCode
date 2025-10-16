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
    def findSmallestInteger(self, nums: List[int], value: int) -> int:
        retVal = 0

        mp = Counter(x % value for x in nums)
        while mp[retVal % value] > 0:
            mp[retVal % value] -= 1
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, value in [[[1, -10, 7, 13, 6, 8], 5], [[1, -10, 7, 13, 6, 8], 7]]:
            # /* Example
            #  *  Input: nums = [1,-10,7,13,6,8], value = 5
            #  *  Output: 4
            #  *
            #  *  Input: nums = [1,-10,7,13,6,8], value = 7
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, value = %s", nums, value)

            retVal = pSolution.findSmallestInteger(nums, value)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
