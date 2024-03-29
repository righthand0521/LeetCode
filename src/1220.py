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

    def countVowelPermutation(self, n: int) -> int:
        retVal = 0

        # dp[i][j]: length is i and last character is j, j = 0, 1, 2, 3, 4 that means a, e, i, o, u.
        # dp[i][0] = dp[i−1][1]+dp[i−1][2]+dp[i−1][4]
        # dp[i][1] = dp[i−1][0]+dp[i−1][2]
        # dp[i][2] = dp[i−1][1]+dp[i−1][3]
        # dp[i][3] = dp[i−1][2]
        # dp[i][4] = dp[i−1][2]+dp[i−1][3] 
        dp = (1, 1, 1, 1, 1)
        for _ in range(n - 1):
            dp1 = (dp[1] + dp[2] + dp[4]) % self.MODULO
            dp2 = (dp[0] + dp[2]) % self.MODULO
            dp3 = (dp[1] + dp[3]) % self.MODULO
            dp4 = dp[2]
            dp5 = (dp[2] + dp[3]) % self.MODULO
            dp = (dp1, dp2, dp3, dp4, dp5)
        retVal = sum(dp) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [1, 2, 5]:
            # /* Example
            #  *  Input: n = 1
            #  *  Output: 5
            #  *
            #  *  Input: n = 2
            #  *  Output: 10
            #  *
            #  *  Input: n = 5
            #  *  Output: 68
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.countVowelPermutation(n)
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
