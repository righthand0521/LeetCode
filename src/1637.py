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
    def maxWidthOfVerticalArea(self, points: List[List[int]]) -> int:
        retVal = 0

        points.sort()

        pointsSize = len(points)
        for i in range(1, pointsSize):
            retVal = max(retVal, (points[i][0]-points[i-1][0]))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[8, 7], [9, 9], [7, 4], [9, 7]], [[3, 1], [9, 0], [1, 0], [1, 4], [5, 3], [8, 8]]]:
            # /* Example
            #  *  Input: points = [[8,7],[9,9],[7,4],[9,7]]
            #  *  Output: 1
            #  *
            #  *  Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
            #  *  Output: 3
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.maxWidthOfVerticalArea(points)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
