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
        self.MODULO = 10 ** 9 + 7   # Since the answer can be very large, return it modulo 10^9 + 7.

    def productQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        retVal = []

        bins = []
        rep = 1
        while n > 0:
            if n % 2 == 1:
                bins.append(rep)
            n //= 2
            rep *= 2

        for left, right in queries:
            cur = 1
            for i in range(left, right + 1):
                cur = cur * bins[i] % self.MODULO
            retVal.append(cur)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, queries in [[15, [[0, 1], [2, 2], [0, 3]]], [2, [[0, 0]]]]:
            # /* Example
            #  *  Input: n = 15, queries = [[0,1],[2,2],[0,3]]
            #  *  Output: [2,4,64]
            #  *
            #  *  Input: n = 2, queries = [[0,0]]
            #  *  Output: [2]
            #  */
            logging.info("Input: n = %s, queries = %s", n, queries)

            retVal = pSolution.productQueries(n, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
