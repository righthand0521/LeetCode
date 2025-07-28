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
    def uniquePaths(self, m: int, n: int) -> int:
        retVal = 0

        # /* Example: 3x7
        #  *     |  0  1  2  3  4  5  6
        #  *  ---+----------------------
        #  *  0  |  1  1  1  1  1  1  1
        #  *  1  |  1  2  3  4  5  6  7
        #  *  2  |  1  3  6 10 15 21 28
        #  */
        dp = [[1 for j in range(n)] for _ in range(m)]
        for i in range(1, m):
            dp[i][0] = 1
        for i in range(1, n):
            dp[0][i] = 1

        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = dp[i-1][j] + dp[i][j-1]
        retVal = dp[m-1][n-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for m, n in zip([3, 3, 5, 16, 13, 51], [7, 2, 10, 16, 23, 9]):
            # /* Example
            #  *  Input: m = 3, n = 7
            #  *  Output: 28
            #  *
            #  *  Input: m = 3, n = 2
            #  *  Output: 3
            #  *
            #  *  Input: m = 5, n = 10
            #  *  Output: 715
            #  *
            #  *  Input: m = 16, n = 16
            #  *  Output: 155117520
            #  *
            #  *  Input: m = 13, n = 23
            #  *  Output: 548354040
            #  *
            #  *  Input: m = 51, n = 9
            #  *  Output: 1916797311
            #  */
            logging.info("Input: m = %d, n = %d", m, n)

            retVal = pSolution.uniquePaths(m, n)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
