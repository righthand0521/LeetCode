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
    # https://leetcode.com/problems/new-21-game/solutions/132334/one-pass-dp-o-n/
    def new21Game(self, n: int, k: int, maxPts: int) -> float:
        retVal = 1

        if k == 0 or n >= k + maxPts:
            return retVal

        # dp[i] is the probability that we get points i at some moment.
        # 1 - dp[i]is the probability that we skip the points i.
        dp = [1.0] + [0.0] * n

        # maxPtsSum = sum(last maxPts dp values)
        maxPtsSum = 1.0

        # dp[i] = sum(last W dp values) / maxPts
        for i in range(1, n + 1):
            dp[i] = maxPtsSum / maxPts
            if i < k:
                maxPtsSum += dp[i]
            if i - maxPts >= 0:
                maxPtsSum -= dp[i - maxPts]
        retVal = sum(dp[k:])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k, maxPts in zip([10, 6, 21], [1, 1, 17], [10, 10, 10]):
            # /* Example
            #  *  Input: n = 10, k = 1, maxPts = 10
            #  *  Output: 1.00000
            #  *
            #  *  Input: n = 6, k = 1, maxPts = 10
            #  *  Output: 0.60000
            #  *
            #  *  Input: n = 21, k = 17, maxPts = 10
            #  *  Output: 0.73278
            #  */
            logging.info("Input: n = %s, k = %s, maxPts = %s", n, k, maxPts)

            retVal = pSolution.new21Game(n, k, maxPts)
            logging.info("Output: %.5f", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
