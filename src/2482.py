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
    def onesMinusZeros(self, grid: List[List[int]]) -> List[List[int]]:
        retVal = [[]]

        # m == grid.length, n == grid[i].length, 1 <= m, n <= 10^5.
        rowSize = len(grid)
        colSize = len(grid[0])
        retVal = [[0 for _ in range(colSize)] for _ in range(rowSize)]

        rowSum = [0] * rowSize
        colSum = [0] * colSize
        for i in range(rowSize):
            for j in range(colSize):
                # grid[i][j] is either 0 or 1.
                rowSum[i] += grid[i][j]
                colSum[j] += grid[i][j]

        for i in range(rowSize):
            for j in range(colSize):
                retVal[i][j] = rowSum[i] + colSum[j]
                retVal[i][j] -= (rowSize - rowSum[i])
                retVal[i][j] -= (colSize - colSum[j])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 1, 1], [1, 0, 1], [0, 0, 1]], [[1, 1, 1], [1, 1, 1]]]:
            # /* Example
            #  *  Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
            #  *  Output: [[0,0,4],[0,0,4],[-2,-2,2]]
            #  *
            #  *  Input: grid = [[1,1,1],[1,1,1]]
            #  *  Output: [[5,5,5],[5,5,5]]
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.onesMinusZeros(grid)
            logging.info("Output: %s", retVal)

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
