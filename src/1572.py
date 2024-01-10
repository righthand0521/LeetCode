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
    def diagonalSum(self, mat: List[List[int]]) -> int:
        retVal = 0

        row = len(mat)
        for i in range(row):
            retVal += mat[i][i]
            retVal += mat[i][len(mat[i]) - 1 - i]
        if row % 2 == 1:
            retVal -= mat[row // 2][row // 2]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mat in [[[1, 2, 3], [4, 5, 6], [7, 8, 9]], [[1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1]], [[5]]]:
            # /* Example
            #  *  Input: mat = [[1,2,3],
            #                   [4,5,6],
            #                   [7,8,9]]
            #  *  Output: 25
            #  *
            #  *  Input: mat = [[1,1,1,1],
            #                   [1,1,1,1],
            #                   [1,1,1,1],
            #                   [1,1,1,1]]
            #  *  Output: 8
            #  *
            #  *  Input: mat = [[5]]
            #  *  Output: 5
            #  */
            logging.info("Input: mat = %s", mat)

            retVal = pSolution.diagonalSum(mat)
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
