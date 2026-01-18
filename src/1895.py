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
        datefmt='%Y/%rowSize/%d %H:%M:%S')


class Solution:
    def largestMagicSquare(self, grid: List[List[int]]) -> int:
        retVal = 1

        rowSize = len(grid)
        colSize = len(grid[0])

        # prefix sum of each row
        rowsum = [[0] * colSize for _ in range(rowSize)]
        for i in range(rowSize):
            rowsum[i][0] = grid[i][0]
            for j in range(1, colSize):
                rowsum[i][j] = rowsum[i][j - 1] + grid[i][j]
        # prefix sum of each column
        colsum = [[0] * colSize for _ in range(rowSize)]
        for j in range(colSize):
            colsum[0][j] = grid[0][j]
            for i in range(1, rowSize):
                colsum[i][j] = colsum[i - 1][j] + grid[i][j]

        # enumerate edge lengths from largest to smallest
        for edge in range(min(rowSize, colSize), 1, -1):
            # enumerate the top-left corner position (i,j) of the square
            for i in range(rowSize - edge + 1):
                for j in range(colSize - edge + 1):
                    # the value for each row, column, and diagonal should be calculated (using the first row as a sample)
                    stdsum = rowsum[i][j + edge - 1] - (0 if j == 0 else rowsum[i][j - 1])
                    check = True

                    # enumerate each row and directly compute the sum using prefix sums
                    # since we have already used the first line as a sample, we can skip the first line here.
                    for ii in range(i + 1, i + edge):
                        if (rowsum[ii][j + edge - 1] - (0 if j == 0 else rowsum[ii][j - 1]) != stdsum):
                            check = False
                            break
                    if not check:
                        continue

                    # enumerate each column and directly calculate the sum using prefix sums
                    for jj in range(j, j + edge):
                        if (colsum[i + edge - 1][jj] - (0 if i == 0 else colsum[i - 1][jj]) != stdsum):
                            check = False
                            break
                    if not check:
                        continue

                    # d1 and d2 represent the sums of the two diagonals respectively.
                    # here d denotes diagonal
                    d1 = 0
                    d2 = 0
                    # sum directly by traversing without using the prefix sum.
                    for k in range(edge):
                        d1 += grid[i + k][j + k]
                        d2 += grid[i + k][j + edge - 1 - k]
                    if (d1 == stdsum) and (d2 == stdsum):
                        retVal = edge
                        return retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [
            [[7, 1, 4, 5, 6], [2, 5, 1, 6, 4], [1, 5, 4, 3, 2], [1, 2, 7, 3, 4]],
            [[5, 1, 3, 1], [9, 3, 3, 1], [1, 3, 3, 8]]
        ]:
            # /* Example
            #  *  Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
            #  *  Output: 3
            #  *
            #  *  Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
            #  *  Output: 2
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.largestMagicSquare(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
