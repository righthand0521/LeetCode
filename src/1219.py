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
    def backtrack(self, grid: List[List[int]], gridSize: int, gridColSize: int, row: int, col: int):
        retVal = 0

        # Base case: this cell is not in the matrix or has no gold
        if (row < 0) or (col < 0) or (row == gridSize) or (col == gridColSize) or (grid[row][col]) == 0:
            return retVal

        # Mark the cell as visited and save the value
        original_val = grid[row][col]
        grid[row][col] = 0

        # Backtrack in each of the four directions
        for i, j in [[0, 1], [0, -1], [1, 0], [-1, 0]]:
            retVal = max(retVal, self.backtrack(grid, gridSize, gridColSize, row + i, col + j))

        # Set the cell back to its original value
        grid[row][col] = original_val

        retVal += original_val

        return retVal

    def getMaximumGold(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        # Search for the path with the maximum gold starting from each cell
        for row in range(gridSize):
            for col in range(gridColSize):
                retVal = max(retVal, self.backtrack(grid, gridSize, gridColSize, row, col))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 6, 0], [5, 8, 7], [0, 9, 0]], [[1, 0, 7], [2, 0, 6], [3, 4, 5], [0, 3, 0], [9, 0, 20]]]:
            # /* Example
            #  *  Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
            #  *  Output: 24
            #  *
            #  *  Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
            #  *  Output: 28
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.getMaximumGold(grid)
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
