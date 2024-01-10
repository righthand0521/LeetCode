import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO  # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S",
    )


class Solution:
    def isReachableAtTime(self, sx: int, sy: int, fx: int, fy: int, t: int) -> bool:
        retVal = False

        diffX = abs(fx - sx)
        diffY = abs(fy - sy)

        if (diffX == 0) and (diffY == 0):
            if t != 1:
                retVal = True
        else:
            if (t - min(diffX, diffY)) >= (max(diffX, diffY) - min(diffX, diffY)):
                retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for sx, sy, fx, fy, t in zip(
            [2, 3, 1, 1], [4, 1, 2, 1], [7, 7, 1, 1], [7, 3, 2, 1], [6, 3, 1, 3]
        ):
            # /* Example
            #  *  Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
            #  *  Output: true
            #  *
            #  *  Input: sx = 3, sy = 1, fx = 7, fy = 3, t = 3
            #  *  Output: false
            #  *
            #  *  Input: sx = 1, sy = 2, fx = 1, fy = 2, t = 1
            #  *  Output: false
            #  *
            #  *  Input: sx = 1, sy = 1, fx = 1, fy = 1, t = 3
            #  *  Output: true
            #  */
            logging.info(
                "Input: sx = %s, sy = %s, fx = %s, fy = %s, t = %s", sx, sy, fx, fy, t
            )

            retVal = pSolution.isReachableAtTime(sx, sy, fx, fy, t)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
