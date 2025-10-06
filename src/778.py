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
    def bfs(self, grid, threshold) -> bool:
        retVal = False

        gridSize = len(grid)

        visited = [[False] * gridSize for _ in range(gridSize)]
        visited[0][0] = True
        bfsQueue = deque([(0, 0)])
        while bfsQueue:
            x, y = bfsQueue.popleft()
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nextX = x + dx
                nextY = y + dy
                if (nextX < 0) or (nextX >= gridSize) or (nextY < 0) or (nextY >= gridSize):
                    continue
                elif visited[nextX][nextY] == True:
                    continue
                elif grid[nextX][nextY] > threshold:
                    continue

                if (nextX == gridSize - 1) and (nextY == gridSize - 1):
                    retVal = True
                    return retVal
                bfsQueue.append((nextX, nextY))
                visited[nextX][nextY] = True

        return retVal

    def swimInWater(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)

        left = 0
        right = gridSize * gridSize - 1
        while left < right:
            middle = (left + right) // 2
            if (grid[0][0] <= middle) and (self.bfs(grid, middle) == True):
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [
            [[0, 2], [1, 3]],
            [[0, 1, 2, 3, 4], [24, 23, 22, 21, 5], [12, 13, 14, 15, 16], [11, 17, 18, 19, 20], [10, 9, 8, 7, 6]]
        ]:
            # /* Example
            #  *  Input: grid = [[0,2],[1,3]]
            #  *  Output: 3
            #  *
            #  *  Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
            #  *  Output: 16
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.swimInWater(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
