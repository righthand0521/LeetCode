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
    def knightProbability(self, n: int, k: int, row: int, column: int) -> float:
        retVal = 0

        directions = [(1, 2), (1, -2), (-1, 2), (-1, -2),
                      (2, 1), (2, -1), (-2, 1), (-2, -1)]

        dp = [[[0] * n for _ in range(n)] for _ in range(k + 1)]
        for step in range(k + 1):
            for i in range(n):
                for j in range(n):
                    if step == 0:
                        dp[step][i][j] = 1
                        continue

                    for diffRow, diffCol in directions:
                        nextRow = i + diffRow
                        nextCol = j + diffCol
                        if (0 <= nextRow < n) and (0 <= nextCol < n):
                            dp[step][i][j] += dp[step - 1][nextRow][nextCol] / 8
        retVal = dp[k][row][column]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k, row, column in zip([3, 1], [2, 0], [0, 0], [0, 0]):
            # /* Example
            #  *  Input: n = 3, k = 2, row = 0, column = 0
            #  *  Output: 0.06250
            #  *
            #  *  Input: n = 1, k = 0, row = 0, column = 0
            #  *  Output: 1.00000
            #  */
            logging.info(
                "Input: n = %s, k = %s, row = %s, column = %s", n, k, row, column)

            retVal = pSolution.knightProbability(n, k, row, column)
            logging.info("Output: %.5f", retVal)

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
