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
    def findClosest(self, x: int, y: int, z: int) -> int:
        retVal = 0

        diffX = abs(x - z)
        diffY = abs(y - z)
        if diffX < diffY:
            retVal = 1
        elif diffX > diffY:
            retVal = 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for x, y, z in [(2, 7, 4), (2, 5, 6), (1, 5, 3)]:
            # /* Example
            #  *  Input: x = 2, y = 7, z = 4
            #  *  Output: 1
            #  *
            #  *  Input: x = 2, y = 5, z = 6
            #  *  Output: 2
            #  *
            #  *  Input: x = 1, y = 5, z = 3
            #  *  Output: 0
            #  */
            logging.info("Input: x = %s, y = %s, z = %s", x, y, z)

            retVal = pSolution.findClosest(x, y, z)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
