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
    def __init__(self) -> None:
        self.directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    def isValid(self, visited: set, row: int, col: int, gridSize: int, gridColSize: int) -> bool:
        retVal = True

        if (row, col) in visited:
            retVal = False
        elif row < 0:
            retVal = False
        elif row >= gridSize:
            retVal = False
        elif col < 0:
            retVal = False
        elif col >= gridColSize:
            retVal = False

        return retVal

    def minimumTime(self, grid: List[List[int]]) -> int:
        retVal = -1

        # If both initial moves require more than 1 second, impossible to proceed
        if (grid[0][1] > 1) and (grid[1][0] > 1):
            return retVal

        gridSize = len(grid)
        gridColSize = len(grid[0])

        visited = set()

        # Priority queue stores (time, row, col), Ordered by minimum time to reach each cell.
        priorityQueue = [(grid[0][0], 0, 0)]
        while priorityQueue:
            time, row, col = heappop(priorityQueue)

            # Check if reached target
            if (row, col) == (gridSize - 1, gridColSize - 1):
                retVal = time
                return retVal

            # Skip if cell already visited
            if (row, col) in visited:
                continue
            visited.add((row, col))

            # Try all four directions
            for dx, dy in self.directions:
                nextRow = row + dx
                nextCol = col + dy
                if self.isValid(visited, nextRow, nextCol, gridSize, gridColSize) == False:
                    continue

                # Calculate the wait time needed to move to next cell
                waitTime = 0
                if (grid[nextRow][nextCol] - time) % 2 == 0:
                    waitTime = 1

                nextTime = max(grid[nextRow][nextCol] + waitTime, time + 1)
                heappush(priorityQueue, (nextTime, nextRow, nextCol))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 1, 3, 2], [5, 1, 2, 5], [4, 3, 8, 6]], [[0, 2, 4], [3, 2, 1], [1, 0, 4]]]:
            # /* Example
            #  *  Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
            #  *  Output: 7
            #  *
            #  *  Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
            #  *  Output: -1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.minimumTime(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
