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
    def findChampion(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        for row in range(gridSize):
            stronger = 0
            for cell in grid[row]:
                stronger += cell

            if stronger == (gridSize-1):
                retVal = row
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 1], [0, 0]], [[0, 0, 1], [1, 0, 1], [0, 0, 0]]]:
            # /* Example
            #  *  Input: grid = [[0,1],[0,0]]
            #  *  Output: 0
            #  *
            #  *  Input: grid = [[0,0,1],[1,0,1],[0,0,0]]
            #  *  Output: 1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.findChampion(grid)
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
