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

    def numWays(self, steps: int, arrLen: int) -> int:
        retVal = 0

        # dp[step][index]: 0 <= step <= steps, 0 <= index <= arrLen-1.
        # => dp[step][index]: 0 <= step <= steps, 0 <= index <= min(arrLen-1, steps).
        # => dpNextStep[index], 0 <= index <= min(arrLen-1, steps).
        maxIndex = min(arrLen - 1, steps)
        dp = [0] * (maxIndex + 1)
        dp[0] = 1
        for _ in range(1, steps + 1):
            dpNextStep = [0] * (maxIndex + 1)
            for j in range(0, maxIndex + 1):
                dpNextStep[j] = dp[j]
                if j - 1 >= 0:
                    dpNextStep[j] = (dpNextStep[j] + dp[j - 1]) % self.MODULO
                if j + 1 <= maxIndex:
                    dpNextStep[j] = (dpNextStep[j] + dp[j + 1]) % self.MODULO
            dp = dpNextStep
        retVal = dp[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for steps, arrLen in zip([3, 2, 4], [2, 4, 2]):
            # /* Example
            #  *  Input: steps = 3, arrLen = 2
            #  *  Output: 4
            #  *
            #  *  Input: steps = 2, arrLen = 4
            #  *  Output: 2
            #  *
            #  *  Input: steps = 4, arrLen = 2
            #  *  Output: 8
            #  */
            logging.info("Input: steps = %s, arrLen = %s", steps, arrLen)

            retVal = pSolution.numWays(steps, arrLen)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
