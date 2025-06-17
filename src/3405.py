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


maxNumber = 10**5  # 1 <= n <= 10^5, 1 <= m <= 10^5
factory = [0] * maxNumber
incertFactory = [0] * maxNumber


class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def qpower(self, x, n):
        retVal = 1

        while n:
            if n & 1:
                retVal = retVal * x % self.MODULO
            x = x * x % self.MODULO
            n >>= 1

        return retVal

    def combine(self, n, m):
        retVal = factory[n] * incertFactory[m] % self.MODULO * incertFactory[n - m] % self.MODULO

        return retVal

    def countGoodArrays(self, n: int, m: int, k: int) -> int:
        retVal = 0

        if factory[0] == 0:
            factory[0] = 1
            for i in range(1, maxNumber):
                factory[i] = factory[i - 1] * i % self.MODULO

            incertFactory[maxNumber - 1] = self.qpower(factory[maxNumber - 1], self.MODULO - 2)
            for i in range(maxNumber - 1, 0, -1):
                incertFactory[i - 1] = incertFactory[i] * i % self.MODULO

        retVal = self.combine(n - 1, k) * m % self.MODULO * self.qpower(m - 1, n - k - 1) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, m, k in zip([3, 4, 5], [2, 2, 2], [1, 2, 0]):
            # /* Example
            #  *  Input: n = 3, m = 2, k = 1
            #  *  Output: 4
            #  *
            #  *  Input: n = 4, m = 2, k = 2
            #  *  Output: 6
            #  *
            #  *  Input: n = 5, m = 2, k = 0
            #  *  Output: 2
            #  */
            logging.info("Input: n = %s, m = %s, k = %s", n, m, k)

            retVal = pSolution.countGoodArrays(n, m, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
