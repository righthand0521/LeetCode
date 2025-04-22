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
        self.MAX_N = 10**4 + 10
        self.MAX_P = 15  # There are up to 15 prime factors

        self.sieve = [0] * self.MAX_N  # // Minimum prime factor
        for i in range(2, self.MAX_N):
            if self.sieve[i] != 0:
                continue
            for j in range(i, self.MAX_N, i):
                self.sieve[j] = i

        self.ps = [[] for _ in range(self.MAX_N)]
        for i in range(2, self.MAX_N):
            x = i
            while x > 1:
                p = self.sieve[x]
                cnt = 0
                while x % p == 0:
                    x //= p
                    cnt += 1
                self.ps[i].append(cnt)

        self.c = [[0] * (self.MAX_P + 1) for _ in range(self.MAX_N + self.MAX_P)]
        self.c[0][0] = 1
        for i in range(1, self.MAX_N + self.MAX_P):
            self.c[i][0] = 1
            for j in range(1, min(i, self.MAX_P) + 1):
                self.c[i][j] = (self.c[i - 1][j] + self.c[i - 1][j - 1]) % self.MODULO

    def idealArrays(self, n: int, maxValue: int) -> int:
        retVal = 0

        for x in range(1, maxValue + 1):
            mul = 1
            for p in self.ps[x]:
                mul = mul * self.c[n + p - 1][p] % self.MODULO
            retVal = (retVal + mul) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, maxValue in [(2, 5), (5, 3)]:
            # /* Example
            #  *  Input: n = 2, maxValue = 5
            #  *  Output: 10
            #  *
            #  *  Input: n = 5, maxValue = 3
            #  *  Output: 11
            #  */
            logging.info("Input: n = %s, maxValue = %s", n, maxValue)

            retVal = pSolution.idealArrays(n, maxValue)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
