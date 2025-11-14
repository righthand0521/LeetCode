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
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:
        retVal = []

        diff = [[0] * (n + 1) for _ in range(n + 1)]
        for row1, col1, row2, col2 in queries:
            diff[row1][col1] += 1
            diff[row2 + 1][col1] -= 1
            diff[row1][col2 + 1] -= 1
            diff[row2 + 1][col2 + 1] += 1

        retVal = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                x1 = 0
                if i != 0:
                    x1 = retVal[i - 1][j]

                x2 = 0
                if j != 0:
                    x2 = retVal[i][j - 1]

                x3 = 0
                if (i != 0) and (j != 0):
                    x3 = retVal[i - 1][j - 1]

                retVal[i][j] = diff[i][j] + x1 + x2 - x3

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, queries in [[3, [[1, 1, 2, 2], [0, 0, 1, 1]]], [2, [[0, 0, 1, 1]]]]:
            # /* Example
            #  *  Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
            #  *  Output: [[1,1,0],[1,2,1],[0,1,1]]
            #  *
            #  *  Input: n = 2, queries = [[0,0,1,1]]
            #  *  Output: [[1,1],[1,1]]
            #  */
            logging.info("Input: n = %s, queries = %s", n, queries)

            retVal = pSolution.rangeAddQueries(n, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
