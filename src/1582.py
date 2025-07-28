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
    def numSpecial(self, mat: List[List[int]]) -> int:
        retVal = 0

        # m == mat.length, n == mat[i].length, 1 <= m, n <= 100.
        rowSize = len(mat)
        colSize = len(mat[0])

        rowSum = [0] * rowSize
        colSum = [0] * colSize
        for i in range(rowSize):
            for j in range(colSize):
                # mat[i][j] is either 0 or 1.
                rowSum[i] += mat[i][j]
                colSum[j] += mat[i][j]

        for i in range(rowSize):
            for j in range(colSize):
                if mat[i][j] != 1:
                    continue
                if (rowSum[i] == 1) and (colSum[j] == 1):
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mat in [[[1, 0, 0], [0, 0, 1], [1, 0, 0]], [[1, 0, 0], [0, 1, 0], [0, 0, 1]]]:
            # /* Example
            #  *  Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
            #  *  Output: 1
            #  *
            #  *  Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
            #  *  Output: 3
            #  */
            logging.info("Input: mat = %s", mat)

            retVal = pSolution.numSpecial(mat)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
