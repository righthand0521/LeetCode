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
    def minFallingPathSum(self, matrix: List[List[int]]) -> int:
        retVal = 0

        # n == matrix.length == matrix[i].length, 1 <= n <= 100.
        rowSize = len(matrix)
        colSize = len(matrix[0])
        for row in range(1, rowSize):
            for col in range(colSize):
                left = matrix[row - 1][col -
                                       1] if (col - 1 >= 0) else float('inf')
                middle = matrix[row - 1][col]
                right = matrix[row - 1][col +
                                        1] if (col + 1 < colSize) else float('inf')

                matrix[row][col] += min(min(left, middle), right)

        retVal = min(matrix[rowSize - 1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[2, 1, 3], [6, 5, 4], [7, 8, 9]],  [[-19, 57], [-40, -5]]]:
            # /* Example
            #  *  Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
            #  *  Output: 13
            #  *
            #  *  Input: matrix = [[-19,57],[-40,-5]]
            #  *  Output: -59
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.minFallingPathSum(matrix)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
