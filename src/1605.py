import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


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
    def restoreMatrix(self, rowSum: List[int], colSum: List[int]) -> List[List[int]]:
        retVal = []

        rowSumSize = len(rowSum)
        colSumSize = len(colSum)
        retVal = [[0 for _ in range(colSumSize)] for _ in range(rowSumSize)]

        # rowSum = [5,7,10], colSum = [8,6,8]
        #      8 6 8       3 6 8       0 6 8       0 2 8      0 0 8      0 0 0
        #  --+-------  --+-------  --+-------  --+------  --+------- --+-------
        #  5 | 0 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0  0 | 5 0 0  0 | 5 0 0
        #  7 | 0 0 0   7 | 0 0 0   4 | 3 0 0   0 | 3 4 0  0 | 3 4 0  0 | 3 4 0
        # 10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  8 | 0 2 0  0 | 0 2 8
        x = 0
        y = 0
        while (x < rowSumSize) and (y < colSumSize):
            retVal[x][y] = min(rowSum[x], colSum[y])
            rowSum[x] -= retVal[x][y]
            colSum[y] -= retVal[x][y]
            if rowSum[x] == 0:
                x += 1
            else:
                y += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rowSum, colSum in zip([[3, 8], [5, 7, 10]], [[4, 7], [8, 6, 8]]):
            # /* Example
            #  *  Input: rowSum = [3,8], colSum = [4,7]
            #  *  Output: [[3,0], [1,7]]
            #  *
            #  *  Input: rowSum = [5,7,10], colSum = [8,6,8]
            #  *  Output: [[0,5,0], [6,1,0], [2,0,8]]
            #  */
            logging.info("Input: rowSum = %s, colSum = %s", rowSum, colSum)

            retVal = pSolution.restoreMatrix(rowSum, colSum)
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
