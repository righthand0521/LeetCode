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
    def maximumCandies(self, candies: List[int], k: int) -> int:
        retVal = 0

        left = 1
        right = 1 + max(candies)
        while left < right:
            middle = left + (right - left) // 2

            tmpCandies = 0
            for candy in candies:
                tmpCandies += candy // middle

            if tmpCandies >= k:
                left = middle + 1
            else:
                right = middle
        retVal = left - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for candies, k in zip([[5, 8, 6], [2, 5], [1, 2, 3, 4, 10], [4, 7, 5], [5, 6, 4, 10, 10, 1, 1, 2, 2, 2]],
                              [3, 11, 5, 16, 9]):
            # /* Example
            #  *  Input: candies = [5,8,6], k = 3
            #  *  Output: 5
            #  *
            #  *  Input: candies = [2,5], k = 11
            #  *  Output: 0
            #  *
            #  *  Input: candies = [1, 2, 3, 4, 10], k = 5
            #  *  Output: 3
            #  *
            #  *  Input: candies = [4, 7, 5], k = 16
            #  *  Output: 1
            #  *
            #  *  Input: candies = [5, 6, 4, 10, 10, 1, 1, 2, 2, 2], k = 9
            #  *  Output: 3
            #  */
            logging.info("Input: candies = %s, k = %d", candies, k)

            retVal = pSolution.maximumCandies(candies, k)
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
