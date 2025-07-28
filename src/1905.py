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
    def dfs(self, x, y, grid1, grid2, visited):
        retVal = True

        if grid1[x][y] != 1:
            retVal = False

        rowSize = len(grid2)
        colSize = len(grid2[0])
        for direction in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            nextX = x + direction[0]
            nextY = y + direction[1]
            if (nextX < 0) or (nextX >= rowSize):
                continue
            elif (nextY < 0) or (nextY >= colSize):
                continue

            if visited[nextX][nextY] == True:
                continue
            elif grid2[nextX][nextY] != 1:
                continue

            visited[nextX][nextY] = True
            nextCellIsPartOfSubIsland = self.dfs(nextX, nextY, grid1, grid2, visited)
            retVal = (retVal and nextCellIsPartOfSubIsland)

        return retVal

    def countSubIslands(self, grid1: List[List[int]], grid2: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid2)
        colSize = len(grid2[0])
        visited = [[False] * colSize for _ in range(rowSize)]
        for x in range(rowSize):
            for y in range(colSize):
                if visited[x][y] == True:
                    continue
                elif grid2[x][y] != 1:
                    continue

                visited[x][y] = True
                if self.dfs(x, y, grid1, grid2, visited):
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid1, grid2 in zip(
            [[[1, 1, 1, 0, 0], [0, 1, 1, 1, 1], [0, 0, 0, 0, 0], [1, 0, 0, 0, 0], [1, 1, 0, 1, 1]],
             [[1, 0, 1, 0, 1], [1, 1, 1, 1, 1], [0, 0, 0, 0, 0], [1, 1, 1, 1, 1], [1, 0, 1, 0, 1]]],
            [[[1, 1, 1, 0, 0], [0, 0, 1, 1, 1], [0, 1, 0, 0, 0], [1, 0, 1, 1, 0], [0, 1, 0, 1, 0]],
             [[0, 0, 0, 0, 0], [1, 1, 1, 1, 1], [0, 1, 0, 1, 0], [0, 1, 0, 1, 0], [1, 0, 0, 0, 1]]]
        ):
            # /* Example
            #  *  Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]],
            #  *  grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
            #  *  Output: 3
            #  *
            #  *  Input: grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]],
            #  *  grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
            #  *  Output: 2
            #  */
            logging.info("Input: grid1 = %s, grid2 = %s", grid1, grid2)

            retVal = pSolution.countSubIslands(grid1, grid2)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
