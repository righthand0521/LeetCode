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
    def dfs(self, grid: List[List[int]], islandId: int, row: int, col: int) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])
        if (row < 0) or (row >= rowSize) or (col < 0) or (col >= colSize):
            return retVal

        if (grid[row][col] != 1):
            return retVal
        grid[row][col] = islandId

        retVal = 1
        retVal += self.dfs(grid, islandId, row + 1, col)
        retVal += self.dfs(grid, islandId, row - 1, col)
        retVal += self.dfs(grid, islandId, row, col + 1)
        retVal += self.dfs(grid, islandId, row, col - 1)

        return retVal

    def largestIsland(self, grid: List[List[int]]) -> int:
        retVal = 1

        rowSize = len(grid)
        colSize = len(grid[0])

        # Step 1: Mark all islands and calculate their sizes
        islandSizes = {}
        islandId = 2
        for row in range(rowSize):
            for col in range(colSize):
                if grid[row][col] == 1:
                    islandSizes[islandId] = self.dfs(grid, islandId, row, col)
                    islandId += 1

        if not islandSizes:  # If there are no islands, return 1
            return retVal
        elif len(islandSizes) == 1:  # If the entire grid is one island, return its size or size +
            islandId -= 1
            retVal = islandSizes[islandId]
            if islandSizes[islandId] != rowSize * colSize:
                retVal += 1
            return retVal

        # Step 2: Try converting every 0 to 1 and calculate the resulting island size
        for row in range(rowSize):
            for col in range(colSize):
                if grid[row][col] != 0:
                    continue

                neighboringIslands = set()
                if (row + 1 < rowSize) and (grid[row + 1][col] > 1):  # Check down
                    neighboringIslands.add(grid[row + 1][col])
                if (row - 1 >= 0) and (grid[row - 1][col] > 1):  # Check up
                    neighboringIslands.add(grid[row - 1][col])
                if (col + 1 < colSize) and (grid[row][col + 1] > 1):  # Check right
                    neighboringIslands.add(grid[row][col + 1])
                if (col - 1 >= 0) and (grid[row][col - 1] > 1):  # Check left
                    neighboringIslands.add(grid[row][col - 1])

                # Sum the sizes of all unique neighboring islands
                currentIslandSize = 1
                for islandId in neighboringIslands:
                    currentIslandSize += islandSizes[islandId]
                retVal = max(retVal, currentIslandSize)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 0], [0, 1]], [[1, 1], [1, 0]], [[1, 1], [1, 1]]]:
            # /* Example
            #  *  Input: grid = [[1,0],[0,1]]
            #  *  Output: 3
            #  *
            #  *  Input: grid = [[1,1],[1,0]]
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[1,1],[1,1]]
            #  *  Output: 4
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.largestIsland(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
