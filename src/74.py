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
    def __init__(self) -> None:
        self.method = 2

    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        retVal = False

        # m == matrix.length, n == matrix[i].length, 1 <= m, n <= 100
        rowSize = len(matrix)
        colSize = len(matrix[0])

        if self.method == 1:    # Binary Search
            left = 0
            right = rowSize * colSize - 1
            while left <= right:
                middle = left + (right - left) // 2
                middleValue = matrix[middle//colSize][middle % colSize]
                if middleValue == target:
                    retVal = True
                    break
                elif middleValue < target:
                    left = middle + 1
                elif middleValue > target:
                    right = middle - 1
        elif self.method == 2:  # vale
            # /* Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3; Output: true
            #  *      0  1  2   3  |  0  1  2   3  |  0  1   2  3
            #  *  0   1  3  5  [7] |  1  3 [5]  7  |  1 [3]  5  7
            #  *  1  10 11 16  20  | 10 11 16  20  | 10 11  16 20
            #  *  2  23 30 34  60  | 23 30 34  60  | 23 30  34 60
            #  *
            #  * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13; Output: false
            #  *      0  1  2   3  |  0  1  2   3  |  0   1   2   3 |  0   1   2  3 |  0   1   2  3 |   0   1  2  3
            #  *  0   1  3  5  [7] |  1  3  5   7  |  1   3   5   7 |  1   3   5  7 |  1   3   5  7 |   1   3  5  7
            #  *  1  10 11 16  20  | 10 11 16 [20] | 10  11 [16] 20 | 10 [11] 16 20 | 10  11  16 20 |  10  11 16 20
            #  *  2  23 30 34  60  | 23 30 34  60  | 23  30  34  60 | 23  30  34 60 | 23 [30] 34 60 | [23] 30 34 60
            #  */
            row = 0
            col = colSize - 1
            while (row < rowSize) and (col >= 0):
                value = matrix[row][col]
                if value == target:
                    retVal = True
                    break
                elif value < target:
                    row += 1
                elif value > target:
                    col -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print("")

        pSolution = Solution()
        for matrix, target in zip([[[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]], [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]], [[1]]], [3, 13, 0]):
            # /* Example
            #  *  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
            #  *  Output: true
            #  *
            #  *  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
            #  *  Output: false
            #  *
            #  *  Input: matrix = [[1]], target = 0
            #  *  Output: false
            #  */
            logging.info("Input: matrix = %s, target = %d", matrix, target)

            retVal = pSolution.searchMatrix(matrix, target)
            logging.info("Output: %s", retVal)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
