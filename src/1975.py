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
    def maxMatrixSum(self, matrix: List[List[int]]) -> int:
        retVal = 0

        minAbsVal = float("inf")
        negativeCount = 0
        for rows in matrix:
            for cell in rows:
                retVal += abs(cell)
                if cell < 0:
                    negativeCount += 1
                minAbsVal = min(minAbsVal, abs(cell))

        if negativeCount % 2 != 0:
            retVal -= (2 * minAbsVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[1, -1], [-1, 1]], [[1, 2, 3], [-1, -2, -3], [1, 2, 3]]]:
            # /* Example
            #  *  Input: matrix = [[1,-1],[-1,1]]
            #  *  Output: 4
            #  *
            #  *  Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
            #  *  Output: 16
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.maxMatrixSum(matrix)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
