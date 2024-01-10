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
        self.directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        retVal = 0

        if matrix == None:
            return retVal

        matrixSize = len(matrix)
        matrixColSize = len(matrix[0])  # 1 <= m, n <= 200

        @lru_cache(None)
        def dfs(x: int, y: int) -> int:
            ret = 1
            for i, j in self.directions:
                row = x + i
                col = y + j
                if (0 <= row < matrixSize) and (0 <= col < matrixColSize) and matrix[row][col] > matrix[x][y]:
                    ret = max(ret, dfs(row, col) + 1)

            return ret

        for x in range(matrixSize):
            for y in range(matrixColSize):
                retVal = max(retVal, dfs(x, y))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[9, 9, 4], [6, 6, 8], [2, 1, 1]], [[3, 4, 5], [3, 2, 6], [2, 2, 1]], [[1]]]:
            # /* Example
            #  *  Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
            #  *  Output: 4
            #  *
            #  *  Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
            #  *  Output: 4
            #  *
            #  *  Input: matrix = [[1]]
            #  *  Output: 1
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.longestIncreasingPath(matrix)
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
