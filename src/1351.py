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
    def countNegatives(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)

        count = 0
        shift = 0
        for i in range(gridSize):
            shift = count
            count = 0
            gridColSize = len(grid[i])
            for j in range(gridColSize - 1 - shift, -1, -1):
                if grid[i][j] < 0:
                    count += 1

            retVal += count
            retVal += shift

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[4, 3, 2, -1], [3, 2, 1, -1], [1, 1, -1, -2], [-1, -1, -2, -3]], [[3, 2], [1, 0]]]:
            # /* Example
            #  *  Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
            #  *  Output: 8
            #  *
            #  *  Input: grid = [[3,2],[1,0]]
            #  *  Output: 0
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.countNegatives(grid)
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
