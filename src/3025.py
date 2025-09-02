import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import inf


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
    def numberOfPairs(self, points: List[List[int]]) -> int:
        retVal = 0

        points.sort(key=lambda point: (point[0], -point[1]))

        for i in range(len(points) - 1):
            pointA = points[i]
            xMin = pointA[0] - 1
            xMax = inf
            yMin = -inf
            yMax = pointA[1] + 1

            for j in range(i + 1, len(points)):
                pointB = points[j]
                if ((pointB[0] > xMin) and (pointB[0] < xMax) and (pointB[1] > yMin) and (pointB[1] < yMax)):
                    retVal += 1
                    xMin = pointB[0]
                    yMin = pointB[1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[1, 1], [2, 2], [3, 3]], [[6, 2], [4, 4], [2, 6]], [[3, 1], [1, 3], [1, 1]]]:
            # /* Example
            #  *  Input: points = [[1,1],[2,2],[3,3]]
            #  *  Output: 0
            #  *
            #  *  Input: points = [[6,2],[4,4],[2,6]]
            #  *  Output: 2
            #  *
            #  *  Input: points = [[3,1],[1,3],[1,1]]
            #  *  Output: 2
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.numberOfPairs(points)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
