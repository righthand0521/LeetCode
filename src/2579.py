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
    def coloredCells(self, n: int) -> int:
        retVal = 0

        # /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
        #  *  = 1 + 4 x (1 + 2 + ... + (n-1))
        #  *  = 1 + 4 x (n x (n-1) / 2)
        #  *  = 1 + 2 x n x (n-1)
        #  */
        retVal = 1 + 2 * n * (n - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [1, 2]:
            # /* Example
            #  *  Input: n = 1
            #  *  Output: 1
            #  *
            #  *  Input: n = 2
            #  *  Output: 5
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.coloredCells(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
