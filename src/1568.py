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
        self.Directions = [(0, 1), (0, -1), (1, 0), (-1, 0),]

    class ArticulationPointInfo:
        def __init__(self, hasArticulationPoint, time):
            self.hasArticulationPoint = hasArticulationPoint
            self.time = time

    def findArticulationPoints(self, grid: List[List[int]], row: int, col: int,
                               discoveryTime: List[List[int]],
                               lowestReachable: List[List[int]],
                               parentCell: List[List[int]],
                               apInfo: ArticulationPointInfo):
        rowSize = len(grid)
        colSize = len(grid[0])

        discoveryTime[row][col] = apInfo.time
        apInfo.time += 1
        lowestReachable[row][col] = discoveryTime[row][col]

        children = 0
        for direction in self.Directions:
            x = row + direction[0]
            y = col + direction[1]
            if (x < 0) or (x >= rowSize):
                continue
            elif (y < 0) or (y >= colSize):
                continue
            elif grid[x][y] != 1:
                continue

            if discoveryTime[x][y] == -1:
                children += 1

                parentCell[x][y] = row * colSize + col
                self.findArticulationPoints(grid, x, y, discoveryTime, lowestReachable, parentCell, apInfo)

                # Update lowest reachable time
                lowestReachable[row][col] = min(lowestReachable[row][col], lowestReachable[x][y])
                # Check for articulation point condition
                if (lowestReachable[x][y] >= discoveryTime[row][col]) and (parentCell[row][col] != -1):
                    apInfo.hasArticulationPoint = True
            elif x * colSize + y != parentCell[row][col]:
                # Update lowest reachable time for back edge
                lowestReachable[row][col] = min(lowestReachable[row][col], discoveryTime[x][y])

        # Root of DFS tree is an articulation point if it has more than one child
        if (parentCell[row][col] == -1) and (children > 1):
            apInfo.hasArticulationPoint = True

    def minDays(self, grid: List[List[int]]) -> int:
        retVal = 2

        rowSize = len(grid)
        colSize = len(grid[0])

        # Time when a cell is first discovered
        discoveryTime = [[-1] * colSize for _ in range(rowSize)]
        # Lowest discovery time reachable from the subtree rooted at this cell
        lowestReachable = [[-1] * colSize for _ in range(rowSize)]
        # Parent of each cell in DFS tree
        parentCell = [[-1] * colSize for _ in range(rowSize)]

        apInfo = self.ArticulationPointInfo(False, 0)
        landCells = 0
        islandCount = 0
        for x in range(rowSize):
            for y in range(colSize):
                if grid[x][y] != 1:
                    continue
                landCells += 1

                if discoveryTime[x][y] != -1:
                    continue
                self.findArticulationPoints(grid, x, y, discoveryTime, lowestReachable, parentCell, apInfo)
                islandCount += 1

        if islandCount == 0 or islandCount >= 2:
            retVal = 0  # Already disconnected or no land
        elif landCells == 1:
            retVal = 1  # Only one land cell
        elif apInfo.hasArticulationPoint:
            retVal = 1  # An articulation point exists

        return retVal  # Need to remove any two land cells


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 1, 1, 0], [0, 1, 1, 0], [0, 0, 0, 0]], [[1, 1]]]:
            # /* Example
            #  *  Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
            #  *  Output: 2
            #  *
            #  *  Input: grid = [[1,1]]
            #  *  Output: 2
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.minDays(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
