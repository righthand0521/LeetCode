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


class Query:
    def __init__(self, index: int, value: int):
        self.index = index
        self.value = value


class Cell:
    def __init__(self, row: int, col: int, value: int):
        self.row = row
        self.col = col
        self.value = value


class UnionFind:
    def __init__(self, n: int):
        self.parent = [-1] * n
        self.size = [1] * n

    def find(self, node: int) -> int:
        retVal = 0

        if self.parent[node] < 0:
            retVal = node
        else:
            retVal = self.find(self.parent[node])

        return retVal

    def union(self, nodeA: int, nodeB: int) -> bool:
        retVal = True

        rootA = self.find(nodeA)
        rootB = self.find(nodeB)
        if rootA == rootB:
            retVal = False
            return retVal

        if self.size[rootA] > self.size[rootB]:
            self.parent[rootB] = rootA
            self.size[rootA] += self.size[rootB]
        else:
            self.parent[rootA] = rootB
            self.size[rootB] += self.size[rootA]

        return retVal

    def getSize(self, node: int) -> int:
        retVal = self.size[self.find(node)]

        return retVal


class Solution:
    def __init__(self):
        self.rowDirections = [0, 0, 1, -1]  # Right, Left, Down, Up
        self.colDirections = [1, -1, 0, 0]  # Corresponding column moves

    def maxPoints(self, grid: List[List[int]], queries: List[int]) -> List[int]:
        retVal = []

        rowSize = len(grid)
        colSize = len(grid[0])
        queriesSize = len(queries)

        retVal = [0] * queriesSize

        # Store queries with their original indices to maintain result order
        sortedQueries = [Query(i, val) for i, val in enumerate(queries)]
        sortedQueries.sort(key=lambda x: x.value)  # Sort queries in ascending order

        # Store all grid cells and sort them by value
        sortedCells = [Cell(row, col, grid[row][col]) for row in range(rowSize) for col in range(colSize)]
        sortedCells.sort(key=lambda x: x.value)  # Sort cells by value

        totalCells = rowSize * colSize
        uf = UnionFind(totalCells)

        cellIndex = 0
        # Process queries in sorted order
        for query in sortedQueries:
            # Process cells whose values are smaller than the current query value
            while (cellIndex < totalCells) and (sortedCells[cellIndex].value < query.value):
                row = sortedCells[cellIndex].row
                col = sortedCells[cellIndex].col
                cellId = (row * colSize + col)  # Convert 2D position to 1D index

                # Merge the current cell with its adjacent cells that have already been processed
                for direction in range(4):
                    newRow = row + self.rowDirections[direction]
                    newCol = col + self.colDirections[direction]
                    newCellId = (newRow * colSize + newCol)  # Convert 2D position to 1D index
                    if (0 <= newRow < rowSize) and (0 <= newCol < colSize) and (grid[newRow][newCol] < query.value):
                        uf.union(cellId, newCellId)

                cellIndex += 1

            # Get the size of the component containing the top-left cell (0,0)
            retVal[query.index] = 0
            if query.value > grid[0][0]:
                retVal[query.index] = uf.getSize(0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid, queries in [[[[1, 2, 3], [2, 5, 7], [3, 5, 1]], [5, 6, 2]], [[[5, 2, 1], [1, 1, 2]], [3]]]:
            # /* Example
            #  *  Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
            #  *  Output: [5,8,1]
            #  *
            #  *  Input: grid = [[5,2,1],[1,1,2]], queries = [3]
            #  *  Output: [0]
            #  */
            logging.info("Input: grid = %s, queries = %s", grid, queries)
            retVal = pSolution.maxPoints(grid, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
