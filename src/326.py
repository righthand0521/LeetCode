import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import log10


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
    def isPowerOfThree(self, n: int) -> bool:
        retVal = False

        if n <= 0:
            return retVal

        if n % 2 == 0:
            return retVal

        # /* n = 3 ^ x
        # * = > log(n) = x * log(3)
        # * = > x = log(n) / log(3)
        # */
        x = log10(n) / log10(3)
        if x - int(x) == 0:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [27, 0, -1]:
            # /* Example
            #  *  Input: n = 27
            #  *  Output: true
            #  *
            #  *  Input: n = 0
            #  *  Output: false
            #  *
            #  *  Input: n = -1
            #  *  Output: false
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.isPowerOfThree(n)
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
