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
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(matrix)
        colSize = len(matrix[0])

        for x in range(1, rowSize):
            for y in range(colSize):
                if matrix[x][y] == 1:
                    matrix[x][y] += matrix[x - 1][y]

        for x in range(rowSize):
            matrix[x].sort(reverse=True)
            for y in range(colSize):
                retVal = max(retVal, matrix[x][y] * (y + 1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[0, 0, 1], [1, 1, 1], [1, 0, 1]], [[1, 0, 1, 0, 1]], [[1, 1, 0], [1, 0, 1]]]:
            # /* Example
            #  *  Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
            #  *  Output: 4
            #  *
            #  *  Input: matrix = [[1,0,1,0,1]]
            #  *  Output: 3
            #  *
            #  *  Input: matrix = [[1,1,0],[1,0,1]]
            #  *  Output: 2
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.largestSubmatrix(matrix)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
