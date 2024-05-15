import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from copy import deepcopy
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
        self.direction = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    def isValidCell(self, grid: List[List[int]], i: int, j: int) -> bool:
        retVal = False

        gridSize = len(grid)
        if (0 <= i < gridSize) and (0 <= j < gridSize):
            retVal = True

        return retVal

    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        retVal = -1

        gridSize = len(grid)

        # Mark thieves as 0 and empty cells as -1, and push thieves to the queue
        multi_source_queue = deque()
        for i in range(gridSize):
            for j in range(gridSize):
                if grid[i][j] == 1:
                    # Push thief coordinates to the queue
                    multi_source_queue.append((i, j))
                    grid[i][j] = 0  # Mark thief cell with 0
                else:
                    grid[i][j] = -1  # Mark empty cell with -1

        # Calculate safeness factor for each cell using BFS
        while multi_source_queue:
            size = len(multi_source_queue)
            while size > 0:
                # Check neighboring cells
                curr = multi_source_queue.popleft()
                for d in self.direction:
                    di = curr[0] + d[0]
                    dj = curr[1] + d[1]
                    val = grid[curr[0]][curr[1]]

                    # Check if the cell is valid and unvisited
                    if self.isValidCell(grid, di, dj) and grid[di][dj] == -1:
                        # Update safeness factor and push to the queue
                        grid[di][dj] = val + 1
                        multi_source_queue.append((di, dj))

                size -= 1

        # Priority queue to prioritize cells with higher safeness factor
        # [maximum_safeness_till_now, x-coordinate, y-coordinate]
        pq = [[-grid[0][0], 0, 0]]
        grid[0][0] = -1  # Mark the source cell as visited

        # BFS to find the path with maximum safeness factor
        while pq:
            retVal, i, j = heappop(pq)

            # If reached the destination, return safeness factor
            if (i == gridSize - 1) and (j == gridSize - 1):
                return -retVal

            # Check neighboring cells
            for d in self.direction:
                di = i + d[0]
                dj = j + d[1]

                # Check if the neighboring cell is valid and unvisited
                if self.isValidCell(grid, di, dj) and grid[di][dj] != -1:
                    heappush(pq, [-min(-retVal, grid[di][dj]), di, dj])
                    grid[di][dj] = -1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 0, 0], [0, 0, 0], [0, 0, 1]],
                     [[0, 0, 1], [0, 0, 0], [0, 0, 0]],
                     [[0, 0, 0, 1], [0, 0, 0, 0], [0, 0, 0, 0], [1, 0, 0, 0]]]:
            # /* Example
            #  *  Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
            #  *  Output: 0
            #  *
            #  *  Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
            #  *  Output: 2
            #  *
            #  *  Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
            #  *  Output: 2
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.maximumSafenessFactor(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
