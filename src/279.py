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
    def numSquares(self, n: int) -> int:
        retVal = 0

        if n <= 0:
            return retVal

        dp = [0] + [n+1] * n
        for i in range(1, n+1):
            j = 1
            while (j*j) <= i:
                dp[i] = min(dp[i], dp[i-(j*j)] + 1)
                j += 1
        retVal = dp[n]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [12, 13]:
            # /* Example
            #  *  Input: n = 12
            #  *  Output: 3
            #  *
            #  *  Input: n = 13
            #  *  Output: 2
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.numSquares(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
