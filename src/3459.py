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
    def __init__(self):
        self.directions = [(1, 1), (1, -1), (-1, -1), (-1, 1)]

    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        @cache
        def dfs(cx: int, cy: int, direction: int, turn: bool, target: int) -> int:
            retVal = 0

            nextX = cx + self.directions[direction][0]
            nextY = cy + self.directions[direction][1]
            # If it goes beyond the boundary or the next node's value is not the target value, then return
            if (nextX < 0) or (nextY < 0) or (nextX >= gridSize) or (nextY >= gridColSize):
                return retVal
            if (grid[nextX][nextY] != target):
                return retVal

            # Continue walking in the original direction.
            maxStep = dfs(nextX, nextY, direction, turn, 2 - target)
            if turn == True:
                # Clockwise rotate 90 degrees turn
                maxStep = max(maxStep, dfs(nextX, nextY, (direction + 1) % 4, False, 2 - target))
            retVal = maxStep + 1

            return retVal

        for i in range(gridSize):
            for j in range(gridColSize):
                if grid[i][j] != 1:
                    continue
                for direction in range(4):
                    retVal = max(retVal, dfs(i, j, direction, True, 2) + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [
            [[2, 2, 1, 2, 2], [2, 0, 2, 2, 0], [2, 0, 1, 1, 0], [1, 0, 2, 2, 2], [2, 0, 0, 2, 2]],
            [[2, 2, 2, 2, 2], [2, 0, 2, 2, 0], [2, 0, 1, 1, 0], [1, 0, 2, 2, 2], [2, 0, 0, 2, 2]],
            [[1, 2, 2, 2, 2], [2, 2, 2, 2, 0], [2, 0, 0, 0, 0], [0, 0, 2, 2, 2], [2, 0, 0, 2, 0]],
            [[1]]
        ]:
            # /* Example
            #  *  Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
            #  *  Output: 5
            #  *
            #  *  Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]
            #  *  Output: 5
            #  *
            #  *  Input: grid = [[1]]
            #  *  Output: 1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.lenOfVDiagonal(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
