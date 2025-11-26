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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numberOfPaths(self, grid: List[List[int]], k: int) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])
        dp = [[[0] * k for _ in range(gridColSize + 1)] for _ in range(gridSize + 1)]
        for i in range(1, gridSize + 1):
            for j in range(1, gridColSize + 1):
                if (i == 1) and (j == 1):
                    dp[i][j][grid[0][0] % k] = 1
                    continue
                value = grid[i - 1][j - 1] % k
                for r in range(k):
                    prev_mod = (r - value + k) % k
                    dp[i][j][r] = (dp[i - 1][j][prev_mod] + dp[i][j - 1][prev_mod]) % self.MODULO
        retVal = dp[gridSize][gridColSize][0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid, k in [
            [[[5, 2, 4], [3, 0, 5], [0, 7, 2]], 3],
            [[[0, 0]], 5],
            [[[7, 3, 4, 9], [2, 3, 6, 2], [2, 3, 7, 0]], 1]
        ]:
            # /* Example
            #  *  Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
            #  *  Output: 2
            #  *
            #  *  Input: grid = [[0,0]], k = 5
            #  *  Output: 1
            #  *
            #  *  Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
            #  *  Output: 10
            #  */
            logging.info("Input: grid = %s, k = %s", grid, k)

            retVal = pSolution.numberOfPaths(grid, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
