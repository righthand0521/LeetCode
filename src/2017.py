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
    def gridGame(self, grid: List[List[int]]) -> int:
        retVal = 0

        colSize = len(grid[0])
        firstRowSum = sum(grid[0])
        secondRowSum = 0
        minimumSum = float("inf")
        for turnIndex in range(colSize):
            firstRowSum -= grid[0][turnIndex]
            minimumSum = min(minimumSum, max(firstRowSum, secondRowSum))
            secondRowSum += grid[1][turnIndex]
        retVal = minimumSum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[2, 5, 4], [1, 5, 1]], [[3, 3, 1], [8, 5, 2]], [[1, 3, 1, 15], [1, 3, 3, 1]]]:
            # /* Example
            #  *  Input: grid = [[2,5,4],[1,5,1]]
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[3,3,1],[8,5,2]]
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[1,3,1,15],[1,3,3,1]]
            #  *  Output: 7
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.gridGame(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
