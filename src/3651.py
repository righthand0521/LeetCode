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
    def minCost(self, grid: List[List[int]], k: int) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        points = [(i, j) for i in range(rowSize) for j in range(colSize)]
        points.sort(key=lambda p: grid[p[0]][p[1]])
        pointsSize = len(points)
        costs = [[float("inf")] * colSize for _ in range(rowSize)]
        for _ in range(k + 1):
            minCost = float("inf")

            j = 0
            for i in range(pointsSize):
                x = points[i][0]
                y = points[i][1]
                minCost = min(minCost, costs[x][y])

                if ((i + 1 < pointsSize) and (grid[x][y] == grid[points[i + 1][0]][points[i + 1][1]])):
                    i += 1
                    continue

                for r in range(j, i + 1):
                    costs[points[r][0]][points[r][1]] = minCost

                j = i + 1

            for i in range(rowSize - 1, -1, -1):
                for j in range(colSize - 1, -1, -1):
                    if (i == rowSize - 1) and (j == colSize - 1):
                        costs[i][j] = 0
                        continue

                    if i != rowSize - 1:
                        costs[i][j] = min(costs[i][j], costs[i + 1][j] + grid[i + 1][j])

                    if j != colSize - 1:
                        costs[i][j] = min(costs[i][j], costs[i][j + 1] + grid[i][j + 1])

        retVal = costs[0][0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid, k in [[[[1, 3, 3], [2, 5, 4], [4, 3, 5]], 2], [[[1, 2], [2, 3], [3, 4]], 1]]:
            # /* Example
            #  *  Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2
            #  *  Output: 7
            #  *
            #  *  Input: grid = [[1,2],[2,3],[3,4]], k = 1
            #  *  Output: 9
            #  */
            logging.info("Input: grid = %s, k = %s", grid, k)

            retVal = pSolution.minCost(grid, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
