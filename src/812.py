import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate, combinations
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
    def area(self, p: int, q: int, r: int) -> float:
        retVal = .5 * abs((p[0]*q[1]) + (q[0]*r[1]) + (r[0]*p[1]) - (p[1]*q[0]) - (q[1]*r[0]) - (r[1]*p[0]))

        return retVal

    def largestTriangleArea(self, points: List[List[int]]) -> float:
        retVal = 0

        for triangle in combinations(points, 3):
            retVal = max(retVal, self.area(*triangle))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[0, 0], [0, 1], [1, 0], [0, 2], [2, 0]], [[1, 0], [0, 0], [0, 1]]]:
            # /* Example
            #  *  Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
            #  *  Output: 2.00000
            #  *
            #  *  Input: points = [[1,0],[0,0],[0,1]]
            #  *  Output: 0.50000
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.largestTriangleArea(points)
            logging.info("Output: %.5f", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
