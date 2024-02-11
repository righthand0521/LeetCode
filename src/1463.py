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
    def cherryPickup(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        dp = [[[-1] * colSize for _ in range(colSize)] for _ in range(rowSize)]
        dp[0][0][colSize-1] = grid[0][0] + grid[0][colSize-1]
        for i in range(1, rowSize):
            for j in range(colSize):
                for k in range(colSize):
                    a = -1
                    if (i > 0) and (j > 0) and (k > 0):
                        a = dp[i-1][j-1][k-1]

                    b = -1
                    if (i > 0) and (j > 0):
                        b = dp[i-1][j-1][k]

                    c = -1
                    if (i > 0) and (j > 0) and (k + 1 < colSize):
                        c = dp[i-1][j-1][k+1]

                    d = -1
                    if (i > 0) and (k > 0):
                        d = dp[i-1][j][k-1]

                    e = -1
                    if i > 0:
                        e = dp[i-1][j][k]

                    f = -1
                    if (i > 0) and (k + 1 < colSize):
                        f = dp[i-1][j][k+1]


                    g = -1
                    if (i > 0) and (j + 1 < colSize) and (k > 0):
                        g = dp[i-1][j+1][k-1]

                    h = -1
                    if (i > 0) and (j + 1 < colSize):
                        h = dp[i-1][j+1][k]

                    t = -1
                    if (i > 0) and (j + 1 < colSize) and (k + 1 < colSize):
                        t = dp[i-1][j+1][k+1]

                    temp = max(a, b, c, d, e, f, g, h, t)
                    if temp == -1:
                        dp[i][j][k] = -1
                    else:
                        if j == k:
                            dp[i][j][k] = temp + grid[i][j]
                        else:
                            dp[i][j][k] = temp + grid[i][j] + grid[i][k]

        for i in range(colSize):
            for j in range(colSize):
                retVal = max(retVal, dp[rowSize-1][i][j])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[3, 1, 1], [2, 5, 1], [1, 5, 5], [2, 1, 1]],
                     [[1, 0, 0, 0, 0, 0, 1], [2, 0, 0, 0, 0, 3, 0], [2, 0, 9, 0, 0, 0, 0], [0, 3, 0, 5, 4, 0, 0], [1, 0, 2, 3, 0, 0, 6]]]:
            # /* Example
            #  *  Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
            #  *  Output: 24
            #  *
            #  *  Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
            #  *  Output: 28
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.cherryPickup(grid)
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
