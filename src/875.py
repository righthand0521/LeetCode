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
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        retVal = 0

        left = 1
        right = max(piles)
        while left < right:
            middle = left + (right - left) // 2

            useHour = 0
            for pile in piles:
                useHour += ((pile + middle - 1) // middle)

            if useHour > h:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for piles, h in zip([[3, 6, 7, 11], [30, 11, 23, 4, 20], [30, 11, 23, 4, 20]], [8, 5, 6]):
            # /* Example
            #  *  Input: piles = [3,6,7,11], h = 8
            #  *  Output: 4
            #  *
            #  *  Input: piles = [30,11,23,4,20], h = 5
            #  *  Output: 30
            #  *
            #  *  Input: piles = [30,11,23,4,20], h = 6
            #  *  Output: 23
            #  */
            logging.info("Input: piles = %s, h = %s", piles, h)

            retVal = pSolution.minEatingSpeed(piles, h)
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
