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
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        retVal = 0

        matrixSize = len(matrix)
        matrixColSize = len(matrix[0])

        # m == matrix.length, n == matrix[i].length, 1 <= m, n <= 300
        if (matrixSize == 0) or (matrixColSize == 0):
            return retVal

        dp = [[0] * matrixColSize for _ in range(matrixSize)]
        maxSide = 0
        for i in range(matrixSize):
            for j in range(matrixColSize):
                if matrix[i][j] != '1':
                    continue

                if ((i == 0) or (j == 0)):
                    dp[i][j] = 1
                else:
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1
                maxSide = max(maxSide, dp[i][j])

        retVal = maxSide * maxSide

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[["1", "0", "1", "0", "0"], ["1", "0", "1", "1", "1"], ["1", "1", "1", "1", "1"], ["1", "0", "0", "1", "0"]],
                       [["0", "1"], ["1", "0"]],
                       [["0"]]]:
            # /* Example
            #  *  Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
            #  *  Output: 4
            #  *
            #  *  Input: matrix = [["0","1"],["1","0"]]
            #  *  Output: 1
            #  *
            #  *  Input: matrix = [["0"]]
            #  *  Output: 0
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.maximalSquare(matrix)
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
