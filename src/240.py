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
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        retVal = False

        # m == matrix.length, n == matrix[i].length, 1 <= n, m <= 300
        rowSize = len(matrix)
        colSize = len(matrix[0])

        # /* Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
        #  *      0  1  2  3  4   |  0   1   2    3  4  |  0   1   2  3  4
        #  *  0   1  4  7 11 [15] |  1  [4] [7] [11] 15 |  1   4   7 11 15
        #  *  1   2  5  8 12  19  |  2   5   8   12  19 |  2  [5]  8 12 19
        #  *  2   3  6  9 16  22  |  3   6   9   16  22 |  3   6   9 16 22
        #  *  3  10 13 14 17  24  | 10  13  14   17  24 | 10  13  14 17 24
        #  *  4  18 21 23 26  30  | 18  21  23   26  30 | 18  21  23 26 30
        #  *
        #  * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
        #  *      0  1  2  3  4   |  0  1  2  3   4  |  0  1  2   3   4 |  0   1    2   3  4 |   0   1  2  3  4
        #  *  0   1  4  7 11 [15] |  1  4  7 11  15  |  1  4  7  11  15 |  1   4    7  11 15 |   1   4  7 11 15
        #  *  1   2  5  8 12  19  |  2  5  8 12 [19] |  2  5  8  12  19 |  2   5    8  12 19 |   2   5  8 12 19
        #  *  2   3  6  9 16  22  |  3  6  9 16 [22] |  3  6  9 [16] 22 |  3   6    9  16 22 |   3   6  9 16 22
        #  *  3  10 13 14 17  24  | 10 13 14 17  24  | 10 13 14 [17] 24 | 10  13   14  17 24 |  10  13 14 17 24
        #  *  4  18 21 23 26  30  | 18 21 23 26  30  | 18 21 23 [26] 30 | 18 [21] [23] 26 30 | [18] 21 23 26 30
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
        for matrix, target in zip(
            [[[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22], [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]],
             [[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22], [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]]],
                [5, 20]):
            # /* Example
            #  *  Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
            #  *  Output: true
            #  *
            #  *  Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
            #  *  Output: false
            #  */
            logging.info("Input: matrix = %s, target = %d", matrix, target)

            retVal = pSolution.searchMatrix(matrix, target)
            logging.info("Output: %s", retVal)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
