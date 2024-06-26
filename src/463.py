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
    def islandPerimeter(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])
        for x in range(gridSize):
            for y in range(gridColSize):
                if grid[x][y] == 0:
                    continue

                count = 0
                for i, j in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                    if (x+i < 0) or (x+i >= gridSize) or (y+j < 0) or (y+j >= gridColSize):
                        count += 1
                    elif grid[x+i][y+j] == 0:
                        count += 1
                retVal += count

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 1, 0, 0], [1, 1, 1, 0], [0, 1, 0, 0], [1, 1, 0, 0]], [[1]], [[1, 0]]]:
            # /* Example
            #  *  Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
            #  *  Output: 16
            #  *
            #  *  Input: grid = [[1]]
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[1,0]]
            #  *  Output: 4
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.islandPerimeter(grid)
            logging.info("Output: %d", retVal)

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
