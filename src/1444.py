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

    # https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/solutions/623732/java-c-python-dp-prefixsum-in-matrix-clean-code/
    def ways(self, pizza: List[str], k: int) -> int:
        retVal = 0

        row = len(pizza)
        col = len(pizza[0])
        preSum = [[0] * (col + 1) for _ in range(row + 1)]
        for r in range(row - 1, -1, -1):
            for c in range(col - 1, -1, -1):
                preSum[r][c] = preSum[r][c + 1] + preSum[r + 1][c] - \
                    preSum[r + 1][c + 1] + (pizza[r][c] == 'A')

        @lru_cache(None)
        def dp(k, r, c):
            retVal = 0

            # if the remain piece has no apple -> invalid
            if preSum[r][c] == 0:
                return retVal

            # found valid way after using k-1 cuts
            if k == 0:
                retVal = 1
                return retVal

            # cut horizontally
            for nr in range(r + 1, row):
                if preSum[r][c] - preSum[nr][c] > 0:
                    retVal = (retVal + dp(k - 1, nr, c)) % self.MODULO

            # cut vertically
            for nc in range(c + 1, col):
                if preSum[r][c] - preSum[r][nc] > 0:
                    retVal = (retVal + dp(k - 1, r, nc)) % self.MODULO

            return retVal

        retVal = dp(k - 1, 0, 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for pizza, k in zip([["A..", "AAA", "..."], ["A..", "AA.", "..."], ["A..", "A..", "..."]], [3, 3, 1]):
            # /* Example
            #  *  Input: pizza = ["A..","AAA","..."], k = 3
            #  *  Output: 3
            #  *
            #  *  Input: pizza = ["A..","AA.","..."], k = 3
            #  *  Output: 1
            #  *
            #  *  Input: pizza = ["A..","A..","..."], k = 1
            #  *  Output: 1
            #  */
            logging.info("Input: pizza = %s, k = %d", pizza, k)

            retVal = pSolution.ways(pizza, k)
            logging.info("Output: %d", retVal)

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
