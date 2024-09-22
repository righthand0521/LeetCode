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
    # To count how many numbers exist between prefix1 and prefix2
    def countSteps(self, n: int, prefix1: int, prefix2: int) -> int:
        retVal = 0

        while prefix1 <= n:
            retVal += min(n + 1, prefix2) - prefix1
            prefix1 *= 10
            prefix2 *= 10

        return retVal

    def findKthNumber(self, n: int, k: int) -> int:
        retVal = 1

        k -= 1
        while k > 0:
            step = self.countSteps(n, retVal, retVal + 1)

            # If the steps are less than or equal to k, we skip this prefix's subtree
            if step <= k:
                # Move to the next prefix and decrease k by the number of steps we skip
                retVal += 1
                k -= step
            else:
                # Move to the next level of the tree and decrement k by 1
                retVal *= 10
                k -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([13, 1], [2, 1]):
            # /* Example
            #  *  Input: n = 13, k = 2
            #  *  Output: 10
            #  *
            #  *  Input: n = 1, k = 1
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.findKthNumber(n, k)
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
