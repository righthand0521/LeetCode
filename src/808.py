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
    def soupServings(self, n: int) -> float:
        retVal = 1

        # /* Answers within 10 ^ -5 of the actual answer will be accepted.
        #  *  E(A) = (4 + 3 + 2 + 1) x 0.25 = 2.5
        #  *  E(B) = (0 + 1 + 2 + 3) x 0.25 = 1.5
        #  *
        #  *  n = 4475, p ≈ 0.999990211307
        #  *  n = 4476, p ≈ 0.999990468596
        #  *
        #  *  n ≥ 179 x 25
        #  */
        n = (n + 24) // 25
        if n >= 179:
            return retVal

        # https://leetcode.cn/problems/soup-servings/solutions/1982919/by-joneli-ts7a/
        dp = [[0.0] * (n + 1) for _ in range(n + 1)]
        dp[0] = [0.5] + [1.0] * n
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                sum = 0
                sum += dp[max(0, i - 4)][j]
                sum += dp[max(0, i - 3)][max(0, j - 1)]
                sum += dp[max(0, i - 2)][max(0, j - 2)]
                sum += dp[max(0, i - 1)][max(0, j - 3)]
                dp[i][j] = sum / 4
        retVal = dp[n][n]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [50, 100]:
            # /* Example
            #  *  Input: n = 50
            #  *  Output: 0.62500
            #  *
            #  *  Input: n = 100
            #  *  Output: 0.71875
            #  */
            logging.info("Input: n = %s",  n)

            retVal = pSolution.soupServings(n)
            logging.info("Output: %.5f", retVal)

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
