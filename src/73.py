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
    def setZeroes(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        matrixRow = len(matrix)
        matrixCol = len(matrix[0])

        rowHashTable = [0] * matrixRow
        colHashTable = [0] * matrixCol
        for i in range(matrixRow):
            for j in range(matrixCol):
                if matrix[i][j] == 0:
                    rowHashTable[i] = 1
                    colHashTable[j] = 1

        for i in range(matrixRow):
            for j in range(matrixCol):
                if (rowHashTable[i] == 1) or (colHashTable[j] == 1):
                    matrix[i][j] = 0


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[1, 1, 1], [1, 0, 1], [1, 1, 1]], [[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]]]:
            # /* Example
            #  *  Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
            #  *  Output: [[1,0,1],[0,0,0],[1,0,1]]
            #  *
            #  *  Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
            #  *  Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
            #  */
            logging.info("Input: matrix = %s", matrix)

            pSolution.setZeroes(matrix)
            logging.info("Output: %s", matrix)

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
