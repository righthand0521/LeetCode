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
    def countServers(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        rowCounts = [0] * colSize
        colCounts = [0] * rowSize
        for row in range(rowSize):
            for col in range(colSize):
                if grid[row][col] == 1:  # grid[i][j] == 0 or 1
                    rowCounts[col] += 1
                    colCounts[row] += 1

        for row in range(rowSize):
            for col in range(colSize):
                if grid[row][col] == 0:  # grid[i][j] == 0 or 1
                    continue

                if (rowCounts[col] > 1) or (colCounts[row] > 1):
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 0], [0, 1]], [[1, 0], [1, 1]], [[1, 1, 0, 0], [0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 0, 1]]]:
            # /* Example
            #  *  Input: grid = [[1,0],[0,1]]
            #  *  Output: 0
            #  *
            #  *  Input: grid = [[1,0],[1,1]]
            #  *  Output: 3
            #  *
            #  *  Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
            #  *  Output: 4
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.countServers(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
