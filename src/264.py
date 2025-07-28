import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


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
    def nthUglyNumber(self, n: int) -> int:
        retVal = 0

        dp = [0] * (n+1)
        dp[1] = 1

        idx2 = 1
        idx3 = 1
        idx5 = 1
        for i in range(2, n+1):
            num2 = dp[idx2] * 2
            num3 = dp[idx3] * 3
            num5 = dp[idx5] * 5
            dp[i] = min(num2, num3, num5)

            if dp[i] == num2:
                idx2 += 1
            if dp[i] == num3:
                idx3 += 1
            if dp[i] == num5:
                idx5 += 1
        retVal = dp[n]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [10, 1]:
            # /* Example
            #  *  Input: n = 10
            #  *  Output: 12
            #  *
            #  *  Input: n = 1
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.nthUglyNumber(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
