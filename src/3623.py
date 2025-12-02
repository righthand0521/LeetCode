import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from math import atan2


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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def countTrapezoids(self, points: List[List[int]]) -> int:
        retVal = 0

        pointNum = defaultdict(int)
        for point in points:
            pointNum[point[1]] += 1

        totalSum = 0
        for point in pointNum.values():
            edge = point * (point - 1) // 2
            retVal = (retVal + edge * totalSum) % self.MODULO
            totalSum = (totalSum + edge) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[1, 0], [2, 0], [3, 0], [2, 2], [3, 2]], [[0, 0], [1, 0], [0, 1], [2, 1]]]:
            # /* Example
            #  *  Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
            #  *  Output: 3
            #  *
            #  *  Input: points = [[0,0],[1,0],[0,1],[2,1]]
            #  *  Output: 1
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.countTrapezoids(points)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
