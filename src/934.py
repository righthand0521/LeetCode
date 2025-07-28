import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def shortestBridge(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)

        #
        for x in range(gridSize):
            for y in range(gridSize):
                if grid[x][y] == 1:
                    island1x = x
                    island1y = y
                    break
        bfsQueue1 = deque([(island1x, island1y)])
        bfsQueue2 = deque([(island1x, island1y)])
        grid[island1x][island1y] = 2

        #
        while bfsQueue1:
            tmp = []
            for x, y in bfsQueue1:
                for row, col in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
                    if (0 <= row < gridSize) and (0 <= col < gridSize):
                        if grid[row][col] == 1:
                            tmp.append((row, col))
                            bfsQueue2.append((row, col))
                            grid[row][col] = 2
            bfsQueue1 = tmp

        #
        while bfsQueue2:
            tmp = []
            for x, y in bfsQueue2:
                for row, col in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
                    if (0 <= row < gridSize) and (0 <= col < gridSize):
                        if grid[row][col] == 1:
                            return retVal
                        elif grid[row][col] == 0:
                            tmp.append((row, col))
                            grid[row][col] = -1
            bfsQueue2 = tmp
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [
            [[0, 1], [1, 0]],
            [[0, 1, 0], [0, 0, 0], [0, 0, 1]],
            [[1, 1, 1, 1, 1], [1, 0, 0, 0, 1], [1, 0, 1, 0, 1], [1, 0, 0, 0, 1], [1, 1, 1, 1, 1]]
        ]:
            # /* Example
            #  *  Input: grid = [[0,1],[1,0]]
            #  *  Output: 1
            #  *
            #  *  Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
            #  *  Output: 2
            #  *
            #  *  Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
            #  *  Output: 1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.shortestBridge(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
