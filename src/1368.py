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
    def minCost(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        minCost = [[float("inf")] * gridColSize for _ in range(gridSize)]
        minCost[0][0] = 0

        # Direction vectors: right, left, down, up (matching grid values 1,2,3,4)
        direction = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        # Use deque for 0-1 BFS - add zero cost moves to front, cost=1 to back
        bfsQueue = deque([(0, 0)])
        while bfsQueue:
            row, col = bfsQueue.popleft()

            for idx, (dx, dy) in enumerate(direction):
                newRow = row + dx
                newCol = col + dy
                if (newRow < 0) or (newRow >= gridSize) or (newCol < 0) or (newCol >= gridColSize):
                    continue

                cost = 1
                if grid[row][col] == idx + 1:
                    cost = 0
                if minCost[row][col] + cost >= minCost[newRow][newCol]:
                    continue

                minCost[newRow][newCol] = minCost[row][col] + cost

                # Add to back if cost=1, front if cost=0
                if cost == 1:
                    bfsQueue.append((newRow, newCol))
                else:
                    bfsQueue.appendleft((newRow, newCol))

        retVal = minCost[gridSize - 1][gridColSize - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 1, 1, 1], [2, 2, 2, 2], [1, 1, 1, 1], [2, 2, 2, 2]],
                     [[1, 1, 3], [3, 2, 2], [1, 1, 4]],
                     [[1, 2], [4, 3]]]:
            # /* Example
            #  *  Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
            #  *  Output: 3
            #  *
            #  *  Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
            #  *  Output: 0
            #  *
            #  *  Input: grid = [[1,2],[4,3]]
            #  *  Output: 1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.minCost(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
