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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def peopleAwareOfSecret(self, n: int, delay: int, forget: int) -> int:
        retVal = 0

        dp = [1] + [0] * forget
        share = 0
        for i in range(1, n):
            share = (share + dp[(i - delay) % forget] - dp[i % forget]) % self.MODULO
            dp[i % forget] = share
        retVal = sum(dp) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, delay, forget in [[6, 2, 4], [4, 1, 3]]:
            # /* Example
            #  *  Input: n = 6, delay = 2, forget = 4
            #  *  Output: 5
            #  *
            #  *  Input: n = 4, delay = 1, forget = 3
            #  *  Output: 6
            #  */
            logging.info("Input: n = %s, delay = %s, forget = %s", n, delay, forget)

            retVal = pSolution.peopleAwareOfSecret(n, delay, forget)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
