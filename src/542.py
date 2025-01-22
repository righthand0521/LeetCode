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
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        retVal = []

        matSize = len(mat)
        matColSize = len(mat[0])

        maxValue = 10**5  # 1 <= m, n <= 10^4, 1 <= m * n <= 10^4
        retVal = [[maxValue] * matColSize for _ in range(matSize)]
        for i in range(matSize):
            for j in range(matColSize):
                if mat[i][j] == 0:
                    retVal[i][j] = 0
        for i in range(matSize):
            for j in range(matColSize):
                if i - 1 >= 0:
                    retVal[i][j] = min(retVal[i][j], retVal[i - 1][j] + 1)
                if j - 1 >= 0:
                    retVal[i][j] = min(retVal[i][j], retVal[i][j - 1] + 1)
        for i in range(matSize - 1, -1, -1):
            for j in range(matColSize - 1, -1, -1):
                if i + 1 < matSize:
                    retVal[i][j] = min(retVal[i][j], retVal[i + 1][j] + 1)
                if j + 1 < matColSize:
                    retVal[i][j] = min(retVal[i][j], retVal[i][j + 1] + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mat in [[[0, 0, 0], [0, 1, 0], [0, 0, 0]], [[0, 0, 0], [0, 1, 0], [1, 1, 1]]]:
            # /* Example
            #  *  Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
            #  *  Output: [[0,0,0],[0,1,0],[0,0,0]]
            #  *
            #  *  Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
            #  *  Output: [[0,0,0],[0,1,0],[1,2,1]]
            #  */
            logging.info("Input: mat = %s", mat)

            retVal = pSolution.updateMatrix(mat)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
