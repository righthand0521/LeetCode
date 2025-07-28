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
    def orangesRotting(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        bfsQueue = deque()
        for x, rowValue in enumerate(grid):
            for y, value in enumerate(rowValue):
                if value == 2:
                    bfsQueue.append((x, y, 0))

        while bfsQueue:
            x, y, retVal = bfsQueue.popleft()
            for nextX, nextY in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
                if (0 <= nextX < rowSize) and (0 <= nextY < colSize):
                    if grid[nextX][nextY] == 1:
                        grid[nextX][nextY] = 2
                        bfsQueue.append((nextX, nextY, retVal + 1))

        for rowValue in grid:
            if 1 in rowValue:
                retVal = -1
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[2, 1, 1], [1, 1, 0], [0, 1, 1]], [[2, 1, 1], [0, 1, 1], [1, 0, 1]], [[0, 2]]]:
            # /* Example
            #  *  Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
            #  *  Output: -1
            #  *
            #  *  Input: grid = [[0,2]]
            #  *  Output: 0
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.orangesRotting(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
