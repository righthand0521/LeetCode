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

    def numOfArrays(self, n: int, m: int, k: int) -> int:
        retVal = 0

        dp = [[0] * (k + 1) for _ in range(m + 1)]
        prefix = [[0] * (k + 1) for _ in range(m + 1)]
        prevDp = [[0] * (k + 1) for _ in range(m + 1)]
        prevPrefix = [[0] * (k + 1) for _ in range(m + 1)]

        for num in range(1, m + 1):
            dp[num][1] = 1
        for i in range(1, n + 1):
            if i > 1:
                dp = [[0] * (k + 1) for _ in range(m + 1)]

            prefix = [[0] * (k + 1) for _ in range(m + 1)]
            for max_num in range(1, m + 1):
                for cost in range(1, k + 1):
                    answer = (max_num * prevDp[max_num][cost]) % self.MODULO
                    answer = (answer + prevPrefix[max_num - 1][cost - 1]) % self.MODULO

                    dp[max_num][cost] += answer
                    dp[max_num][cost] %= self.MODULO

                    prefix[max_num][cost] = (prefix[max_num - 1][cost] + dp[max_num][cost]) % self.MODULO

            prevDp = dp
            prevPrefix = prefix

        retVal = prefix[m][k]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, m, k in zip([2, 5, 9], [3, 2, 1], [1, 3, 1]):
            # /* Example
            #  *  Input: n = 2, m = 3, k = 1
            #  *  Output: 6
            #  *
            #  *  Input: n = 5, m = 2, k = 3
            #  *  Output: 0
            #  *
            #  *  Input: n = 9, m = 1, k = 1
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, m = %s, k = %s", n, m, k)

            retVal = pSolution.numOfArrays(n, m, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
