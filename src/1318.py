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
    def minFlips(self, a: int, b: int, c: int) -> int:
        retVal = 0

        while ((a > 0) or (b > 0) or (c > 0)):
            if c & 1:
                retVal += ((~((a & 1) | (b & 1))) & 1)
            else:
                retVal += ((a & 1) + (b & 1))

            a >>= 1
            b >>= 1
            c >>= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for a, b, c in zip([2, 4, 1], [6, 2, 2], [5, 7, 3]):
            # /* Example
            #  *  Input: a = 2, b = 6, c = 5
            #  *  Output: 3
            #  *
            #  *  Input: a = 4, b = 2, c = 7
            #  *  Output: 1
            #  *
            #  *  Input: a = 1, b = 2, c = 3
            #  *  Output: 0
            #  */
            logging.info("Input: a = %s, b = %s, c = %s", a, b, c)

            retVal = pSolution.minFlips(a, b, c)
            logging.info("Output: %d", retVal)

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
