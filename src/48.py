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
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """

        matrixSize = len(matrix)

        for i in range(matrixSize):
            matrixColSize = len(matrix[i])
            for j in range(matrixColSize//2):
                matrix[i][j], matrix[i][matrixColSize-j-1] = \
                    matrix[i][matrixColSize-j-1], matrix[i][j]

        for i in range(matrixSize):
            matrixColSize = len(matrix[i])
            for j in range(matrixColSize-i):
                matrix[i][j], matrix[matrixColSize-1-j][matrixSize-1-i] = \
                    matrix[matrixColSize-1-j][matrixSize-1-i], matrix[i][j]


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[1, 2, 3], [4, 5, 6], [7, 8, 9]], [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]]]:
            # /* Example
            #  *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
            #  *  Output: [[7,4,1],[8,5,2],[9,6,3]]
            #  *
            #  *  Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
            #  *  Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
            #  */
            logging.info("Input: matrix = %s", matrix)

            pSolution.rotate(matrix)
            logging.info("Output: %s", matrix)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
