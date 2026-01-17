import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate, combinations
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
    def largestSquareArea(self, bottomLeft: List[List[int]], topRight: List[List[int]]) -> int:
        retVal = 0

        maxSide = 0
        for (bottomleftX, toprightX), (bottomleftY, topRightY,) in combinations(zip(bottomLeft, topRight), 2):
            weight = min(toprightX[0], topRightY[0]) - max(bottomleftX[0], bottomleftY[0])
            high = min(toprightX[1], topRightY[1]) - max(bottomleftX[1], bottomleftY[1])
            maxSide = max(maxSide, min(weight, high))
        retVal = maxSide * maxSide

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for bottomLeft, topRight in [
            [[[1, 1], [2, 2], [3, 1]], [[3, 3], [4, 4], [6, 6]]],
            [[[1, 1], [1, 3], [1, 5]], [[5, 5], [5, 7], [5, 9]]],
            [[[1, 1], [2, 2], [1, 2]], [[3, 3], [4, 4], [3, 4]]],
            [[[1, 1], [3, 3], [3, 1]], [[2, 2], [4, 4], [4, 2]]]
        ]:
            # /* Example
            #  *  Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
            #  *  Output: 1
            #  *
            #  *  Input: bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]
            #  *  Output: 4
            #  *
            #  *  Input: bottomLeft = [[1,1],[2,2],[1,2]], topRight = [[3,3],[4,4],[3,4]]
            #  *  Output: 1
            #  *
            #  *  Input: bottomLeft = [[1,1],[3,3],[3,1]], topRight = [[2,2],[4,4],[4,2]]
            #  *  Output: 0
            #  */
            logging.info("Input: bottomLeft = %s, topRight = %s", bottomLeft, topRight)

            retVal = pSolution.largestSquareArea(bottomLeft, topRight)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
