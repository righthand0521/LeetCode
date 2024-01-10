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
    def minPathSum(self, grid: List[List[int]]) -> int:
        retVal = 0

        # m == grid.length, n == grid[i].length, 1 <= m, n <= 200
        row = len(grid)
        col = len(grid[0])
        dp = [[0 for j in range(col)] for _ in range(row)]

        # /* Example
        #  *    | 0 1 2 |  0     1     2
        #  *  --+-------+------------------
        #  *  0 | 1 3 1 |   (1) 1+(3) 4+(1)
        #  *  1 | 1 5 1 | 1+(1) 2+(5) 5+(1)
        #  *  2 | 4 2 1 | 2+(4) 6+(2) 6+(1)
        #  */
        dp[0][0] = grid[0][0]
        for i in range(1, row):
            dp[i][0] = dp[i-1][0] + grid[i][0]
        for i in range(1, col):
            dp[0][i] = dp[0][i-1] + grid[0][i]

        for i in range(1, row):
            for j in range(1, col):
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
        retVal = dp[row-1][col-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 3, 1], [1, 5, 1], [4, 2, 1]], [[1, 2, 3], [4, 5, 6]]]:
            # /* Example
            #  *  Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
            #  *  Output: 7
            #  *
            #  *  Input: grid = [[1,2,3],[4,5,6]]
            #  *  Output: 12
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.minPathSum(grid)
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
