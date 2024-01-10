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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numRollsToTarget(self, n: int, k: int, target: int) -> int:
        retVal = 0

        # dp[n][target] = dp[n-1][target-x], x = 1, .., k
        #   0 1 2 3 4 5 6 7
        # 0 1 0 0 0 0 0 0 0
        # 1 0 1 1 1 1 1 1 0
        # 2 0 0 1 2 3 4 5 6
        dp = [[0] * (target + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        for i in range(1, n + 1):
            for j in range(target + 1):
                for x in range(1, k + 1):
                    if j - x >= 0:
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - x]) % self.MODULO
        retVal = dp[n][target]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k, target in zip([1, 2, 30], [6, 6, 30], [3, 7, 500]):
            # /* Example
            #  *  Input: n = 1, k = 6, target = 3
            #  *  Output: 1
            #  *
            #  *  Input: n = 2, k = 6, target = 7
            #  *  Output: 6
            #  *
            #  *  Input: n = 30, k = 30, target = 500
            #  *  Output: 222616187
            #  */
            logging.info("Input: n = %s, k = %s, target = %s", n, k, target)

            retVal = pSolution.numRollsToTarget(n, k, target)
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
