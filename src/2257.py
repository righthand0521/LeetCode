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
    def markUnguarded(self, row: int, col: int, grid: List[List[int]]) -> None:
        gridSize = len(grid)
        for x in range(row - 1, -1, -1):
            if (grid[x][col] == 3) or (grid[x][col] == 2):
                break
            grid[x][col] = 1
        for x in range(row + 1, gridSize):
            if (grid[x][col] == 3) or (grid[x][col] == 2):
                break
            grid[x][col] = 1

        gridColSize = len(grid[0])
        for y in range(col - 1, -1, -1):
            if (grid[row][y] == 3) or (grid[row][y] == 2):
                break
            grid[row][y] = 1
        for y in range(col + 1, gridColSize):
            if (grid[row][y] == 3) or (grid[row][y] == 2):
                break
            grid[row][y] = 1

    def countUnguarded(self, m: int, n: int, guards: List[List[int]], walls: List[List[int]]) -> int:
        retVal = 0

        grid = [[0] * n for _ in range(m)]
        for guard in guards:
            grid[guard[0]][guard[1]] = 2
        for wall in walls:
            grid[wall[0]][wall[1]] = 3

        for guard in guards:
            self.markUnguarded(guard[0], guard[1], grid)

        for row in grid:
            for cell in row:
                if cell == 0:
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for m, n, guards, walls in zip([4, 3],
                                       [6, 3],
                                       [[[0, 0], [1, 1], [2, 3]], [[1, 1]]],
                                       [[[0, 1], [2, 2], [1, 4]], [[0, 1], [1, 0], [2, 1], [1, 2]]]):
            # /* Example
            #  *  Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
            #  *  Output: 7
            #  *
            #  *  Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
            #  *  Output: 4
            #  */
            logging.info(
                "Input: m = %s, n = %s, guards = %s, walls = %s", m, n, guards, walls)

            retVal = pSolution.countUnguarded(m, n, guards, walls)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
