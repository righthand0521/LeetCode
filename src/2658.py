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
    def bfs(self, grid, visited, row, col) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        bfsQueue = [(row, col)]
        visited[row][col] = True
        directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        while bfsQueue:
            x, y = bfsQueue.pop(0)
            retVal += grid[x][y]

            for dx, dy in directions:
                nextX = x + dx
                nextY = y + dy
                if (nextX < 0) or (nextX >= rowSize) or (nextY < 0) or (nextY >= colSize):
                    continue

                if (grid[nextX][nextY] != 0) and (visited[nextX][nextY] == False):
                    bfsQueue.append((nextX, nextY))
                    visited[nextX][nextY] = True

        return retVal

    def findMaxFish(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        visited = [[False] * colSize for _ in range(rowSize)]
        for i in range(rowSize):
            for j in range(colSize):
                if (grid[i][j] != 0) and (visited[i][j] == False):
                    retVal = max(retVal, self.bfs(grid, visited, i, j))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 2, 1, 0], [4, 0, 0, 3], [1, 0, 0, 4], [0, 3, 2, 0]],
                     [[1, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 1]]]:
            # /* Example
            #  *  Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
            #  *  Output: 7
            #  *
            #  *  Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
            #  *  Output: 1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.findMaxFish(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
