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

    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:
        retVal = 0

        dp = [1] + [0] * high
        for i in range(1, high+1):
            if i >= zero:
                dp[i] += dp[i - zero]
                dp[i] %= self.MODULO

            if i >= one:
                dp[i] += dp[i - one]
                dp[i] %= self.MODULO

        retVal = sum(dp[low:high+1]) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for low, high, zero, one in zip([3, 2], [3, 3], [1, 1], [1, 2]):
            # /* Example
            #  *  Input: low = 3, high = 3, zero = 1, one = 1
            #  *  Output: 8
            #  *
            #  *  Input: low = 2, high = 3, zero = 1, one = 2
            #  *  Output: 5
            #  */
            logging.info(
                "Input: low = %s, high = %s, zero = %s, one = %s", low, high, zero, one)

            retVal = pSolution.countGoodStrings(low, high, zero, one)
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
