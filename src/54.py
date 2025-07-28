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
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        retVal = []

        rowSize = len(matrix)
        colSize = len(matrix[0])
        maxReturnSize = rowSize * colSize

        returnSize = 0
        for row in range(rowSize // 2 + 1):
            # /* first row: x1, last column: x2, last row: x3, first column: x4.
            #  *
            #  *  (top,left)               (top,right)
            #  *      +------------------------+
            #  *      | 11 | 11 | 11 | 11 | 11 |
            #  *      | 14 | 21 | 21 | 21 | 12 |
            #  *      | 14 | 24 | 31 | 22 | 12 |
            #  *      | 14 | 23 | 23 | 22 | 12 |
            #  *      | 13 | 13 | 13 | 13 | 12 |
            #  *      +------------------------+
            #  * (down,left)              (down,right)
            #  */

            # first row
            for col in range(row, colSize - row):
                retVal.append(matrix[row][col])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal
            if row + 1 == rowSize - row:
                continue

            # last column
            for col in range((row + 1), (rowSize - row)):
                retVal.append(matrix[col][colSize - 1 - row])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal
            if row + 1 == colSize:
                continue

            # last row
            for col in range((colSize - 1 - (row + 1)), (row - 1), -1):
                retVal.append(matrix[rowSize - 1 - row][col])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal

            # first column
            for col in range((rowSize - 1 - (row + 1)), row, -1):
                retVal.append(matrix[col][row])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [
            [[1, 2, 3], [4, 5, 6], [7, 8, 9]],
            [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]],
            [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]],
            [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],
            [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]],
            [[1, 2, 3, 4, 5, 6, 7, 8, 9]],
            [[1], [2], [3], [4], [5], [6], [7], [8], [9], [10]],
            [[1], [2], [3], [4], [5], [6], [7], [8], [9]]
        ]:
            # /* Example
            #  *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
            #  *  Output: [1,2,3,6,9,8,7,4,5]
            #  *
            #  *  Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
            #  *  Output: [1,2,3,4,8,12,11,10,9,5,6,7]
            #  *
            #  *  Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
            #  *  Output: [1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10]
            #  *
            #  *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9],[10,11,12]]
            #  *  Output: [1,2,3,6,9,12,11,10,7,4,5,8]
            #  *
            #  *  Input: matrix = [[1,2,3,4,5,6,7,8,9,10]]
            #  *  Output: [1,2,3,4,5,6,7,8,9,10]
            #  *
            #  *  Input: matrix = [[1,2,3,4,5,6,7,8,9]]
            #  *  Output: [1,2,3,4,5,6,7,8,9]
            #  *
            #  *  Input: matrix = [[1],[2],[3],[4],[5],[6],[7],[8],[9],[10]]
            #  *  Output: [1,2,3,4,5,6,7,8,9,10]
            #  *
            #  *  Input: matrix = [[1],[2],[3],[4],[5],[6],[7],[8],[9]]
            #  *  Output: [1,2,3,4,5,6,7,8,9]
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.spiralOrder(matrix)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
