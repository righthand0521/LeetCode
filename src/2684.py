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
    def maxMoves(self, grid: List[List[int]]) -> int:
        retVal = 0

        row = len(grid)
        col = len(grid[0])
        dp = [[0] * col for _ in range(row)]
        for x in range(row):  # Initialize the first column with moves as 1.
            dp[x][0] = 1

        # Check all three possible previous cells: (x, y-1), (x-1, y-1), (x+1, y-1)
        for y in range(1, col):
            for x in range(row):
                if (grid[x][y] > grid[x][y-1]) and (dp[x][y-1] > 0):
                    dp[x][y] = max(dp[x][y], dp[x][y-1] + 1)

                if ((x - 1 >= 0) and (grid[x][y] > grid[x-1][y-1]) and (dp[x-1][y-1] > 0)):
                    dp[x][y] = max(dp[x][y], dp[x-1][y-1] + 1)

                if ((x + 1 < row) and (grid[x][y] > grid[x+1][y-1]) and (dp[x+1][y-1] > 0)):
                    dp[x][y] = max(dp[x][y], dp[x+1][y-1] + 1)

                retVal = max(retVal, dp[x][y] - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[2, 4, 3, 5], [5, 4, 9, 3], [3, 4, 2, 11], [10, 9, 13, 15]], [[3, 2, 4], [2, 1, 9], [1, 1, 7]]]:
            # /* Example
            #  *  Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
            #  *  Output: 3
            #  *
            #  *  Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
            #  *  Output: 0
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.maxMoves(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
