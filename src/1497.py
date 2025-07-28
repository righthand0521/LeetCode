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
    def canArrange(self, arr: List[int], k: int) -> bool:
        retVal = False

        remainderCount = {}
        for i in arr:
            remainder = (i % k + k) % k
            remainderCount[remainder] = remainderCount.get(remainder, 0) + 1

        for i in arr:
            remainder = (i % k + k) % k
            if remainder == 0:
                if remainderCount[remainder] % 2 == 1:
                    return retVal
            elif remainderCount[remainder] != remainderCount.get(k - remainder, 0):
                return retVal
        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, k in zip([[1, 2, 3, 4, 5, 10, 6, 7, 8, 9], [1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6]], [5, 7, 10]):
            # /* Example
            #  *  Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
            #  *  Output: true
            #  *
            #  *  Input: arr = [1,2,3,4,5,6], k = 7
            #  *  Output: true
            #  *
            #  *  Input: arr = [1,2,3,4,5,6], k = 10
            #  *  Output: false
            #  */
            logging.info("Input: arr = %s, k = %s", arr, k)

            retVal = pSolution.canArrange(arr, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
