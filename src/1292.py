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
        datefmt='%Y/%rowSize/%d %H:%M:%S')


class Solution:
    def getRect(self, P: List[List[int]], x1: int, y1: int, x2: int, y2: int) -> int:
        retVal = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1]

        return retVal

    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:
        retVal = 0

        rowSize = len(mat)
        colSize = len(mat[0])

        P = [[0] * (colSize + 1) for _ in range(rowSize + 1)]
        for i in range(1, rowSize + 1):
            for j in range(1, colSize + 1):
                P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1]

        r = min(rowSize, colSize)
        for i in range(1, rowSize + 1):
            for j in range(1, colSize + 1):
                for c in range(retVal + 1, r + 1):
                    if i + c - 1 > rowSize:
                        break
                    elif j + c - 1 > colSize:
                        break
                    elif self.getRect(P, i, j, i + c - 1, j + c - 1) > threshold:
                        break

                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mat, threshold in [
                [[[1, 1, 3, 2, 4, 3, 2], [1, 1, 3, 2, 4, 3, 2], [1, 1, 3, 2, 4, 3, 2]], 4],
                [[[2, 2, 2, 2, 2], [2, 2, 2, 2, 2], [2, 2, 2, 2, 2], [2, 2, 2, 2, 2], [2, 2, 2, 2, 2]], 1]
        ]:
            # /* Example
            #  *  Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
            #  *  Output: 2
            #  *
            #  *  Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
            #  *  Output: 0
            #  */
            logging.info("Input: mat = %s, threshold = %s", mat, threshold)

            retVal = pSolution.maxSideLength(mat, threshold)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
