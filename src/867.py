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
    def transpose(self, matrix: List[List[int]]) -> List[List[int]]:
        retVal = [[]]

        rowSize = len(matrix[0])
        colSize = len(matrix)
        retVal = [[0] * colSize for _ in range(rowSize)]
        for i, row in enumerate(matrix):
            for j, value in enumerate(row):
                retVal[j][i] = value

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[1, 2, 3], [4, 5, 6], [7, 8, 9]], [[1, 2, 3], [4, 5, 6]]]:
            # /* Example
            #  *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
            #  *  Output: [[1,4,7],[2,5,8],[3,6,9]]
            #  *
            #  *  Input: matrix = [[1,2,3],[4,5,6]]
            #  *  Output: [[1,4],[2,5],[3,6]]
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.transpose(matrix)
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
