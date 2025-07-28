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

    def kInversePairs(self, n: int, k: int) -> int:
        retVal = 0

        dp = [1] + [0] * k
        for i in range(1, n + 1):
            dpCurrent = [0] * (k + 1)
            for j in range(k + 1):
                dpCurrent[j] = 0
                if j - 1 >= 0:
                    dpCurrent[j] = dpCurrent[j - 1]
                if j - i >= 0:
                    dpCurrent[j] -= dp[j - i]
                dpCurrent[j] += dp[j]
                dpCurrent[j] %= self.MODULO
            dp = dpCurrent

        retVal = dp[k]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([3, 3], [0, 1]):
            # /* Example
            #  *  Input: n = 3, k = 0
            #  *  Output: 1
            #  *
            #  *  Input: n = 3, k = 1
            #  *  Output: 2
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.kInversePairs(n, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
