import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        retVal = -1

        if grid[0][0] == 1:
            return retVal

        gridSize = len(grid)

        visitDistance = [[float('inf')] * gridSize for _ in range(gridSize)]
        visitDistance[0][0] = 1
        adjacent = [(-1, -1), (-1, 0), (-1, 1), (0, -1),
                    (0, 1), (1, -1), (1, 0), (1, 1)]
        bfsQueue = deque([(0, 0)])
        while bfsQueue:
            x, y = bfsQueue.popleft()
            if (x == gridSize - 1) and (y == gridSize - 1):
                retVal = visitDistance[x][y]
                break

            for dx, dy in adjacent:
                row = x + dx
                col = y + dy
                if ((row < 0) or (row >= gridSize) or (col < 0) or (col >= gridSize)):
                    continue

                if ((grid[row][col] == 1) or (visitDistance[row][col] <= visitDistance[x][y] + 1)):
                    continue
                visitDistance[row][col] = visitDistance[x][y] + 1
                bfsQueue.append((row, col))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 1], [1, 0]],
                     [[0, 0, 0], [1, 1, 0], [1, 1, 0]],
                     [[1, 0, 0], [1, 1, 0], [1, 1, 0]]]:
            # /* Example
            #  *  Input: grid = [[0,1],[1,0]]
            #  *  Output: 2
            #  *
            #  *  Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
            #  *  Output: -1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.shortestPathBinaryMatrix(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
