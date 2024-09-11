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
    def minBitFlips(self, start: int, goal: int) -> int:
        retVal = 0

        for _ in range(32):
            retVal += (start & 1) ^ (goal & 1)
            start >>= 1
            goal >>= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for start, goal in zip([10, 3], [7, 4]):
            # /* Example
            #  *  Input: start = 10, goal = 7
            #  *  Output: 3
            #  *
            #  *  Input: start = 3, goal = 4
            #  *  Output: 3
            #  */
            logging.info("Input: start = %s, goal = %s", start, goal)

            retVal = pSolution.minBitFlips(start, goal)
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
