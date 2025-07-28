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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
        retVal = 0

        dp = [[0] * n for _ in range(m)]
        dp[startRow][startColumn] = 1

        for _ in range(maxMove):
            dpCurrent = [[0] * n for _ in range(m)]
            for row in range(m):
                for col in range(n):
                    if dp[row][col] <= 0:
                        continue

                    for nextRow, nextCol in [(row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)]:
                        if (0 <= nextRow < m) and (0 <= nextCol < n):
                            dpCurrent[nextRow][nextCol] = (
                                dpCurrent[nextRow][nextCol] + dp[row][col]) % self.MODULO
                        else:
                            retVal = (retVal + dp[row][col]) % self.MODULO

            dp = dpCurrent

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for m, n, maxMove, startRow, startColumn in zip([2, 1], [2, 3], [2, 3], [0, 0], [0, 1]):
            # /* Example
            #  *  Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
            #  *  Output: 6
            #  *
            #  *  Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
            #  *  Output: 12
            #  */
            logging.info("Input: m = %s, n = %s, maxMove = %s, startRow = %s, startColumn = %s",
                         m, n, maxMove, startRow, startColumn)

            retVal = pSolution.findPaths(m, n, maxMove, startRow, startColumn)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
