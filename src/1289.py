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
    def minFallingPathSum(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)

        dp = [[float('inf') for _ in range(gridSize)] for _ in range(gridSize)]
        for i in range(gridSize):
            dp[0][i] = grid[0][i]

        for i in range(gridSize):
            for j in range(gridSize):
                for k in range(gridSize):
                    if j == k:
                        continue
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + grid[i][j])

        retVal = min(dp[gridSize - 1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 2, 3], [4, 5, 6], [7, 8, 9]],  [[7]]]:
            # /* Example
            #  *  Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
            #  *  Output: 13
            #  *
            #  *  Input: grid = [[7]]
            #  *  Output: 7
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.minFallingPathSum(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
