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
    def countSquares(self, matrix: List[List[int]]) -> int:
        retVal = 0

        row = len(matrix)
        col = len(matrix[0])
        dp = [[0] * (col + 1) for _ in range(row + 1)]
        for x in range(row):
            for y in range(col):
                if matrix[x][y] == 0:
                    continue
                dp[x + 1][y + 1] = (min(dp[x][y + 1],dp[x + 1][y], dp[x][y]) + 1)
                retVal += dp[x + 1][y + 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[0, 1, 1, 1], [1, 1, 1, 1], [0, 1, 1, 1]], [[1, 0, 1], [1, 1, 0], [1, 1, 0]]]:
            # /* Example
            #  *  Input: matrix = [[0,1,1,1], [1,1,1,1], [0,1,1,1]]
            #  *  Output: 15
            #  *
            #  *  Input: matrix = [[1,0,1], [1,1,0], [1,1,0]]
            #  *  Output: 7
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.countSquares(matrix)
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
