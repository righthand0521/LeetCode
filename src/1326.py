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
    def minTaps(self, n: int, ranges: List[int]) -> int:
        retVal = -1

        # 1 <= n <= 10^4; ranges.length == n + 1; 0 <= ranges[i] <= 100
        infinity = int(1e9)

        dp = [infinity] * (n + 1)
        dp[0] = 0

        for i in range(n + 1):
            tapStart = max(0, i - ranges[i])
            tapEnd = min(n, i + ranges[i])
            for j in range(tapStart, tapEnd + 1):
                dp[tapEnd] = min(dp[tapEnd], dp[j] + 1)

        if dp[n] != infinity:
            retVal = dp[n]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, ranges in zip([5, 3], [[3, 4, 1, 1, 0, 0], [0, 0, 0, 0]]):
            # /* Example
            #  *  Input: n = 5, ranges = [3,4,1,1,0,0]
            #  *  Output: 1
            #  *
            #  *  Input: n = 3, ranges = [0,0,0,0]
            #  *  Output: -1
            #  */
            logging.info("Input: n = %s, ranges = %s", n, ranges)

            retVal = pSolution.minTaps(n, ranges)
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
