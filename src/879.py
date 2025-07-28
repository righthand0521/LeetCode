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

    def profitableSchemes(self, n: int, minProfit: int, group: List[int], profit: List[int]) -> int:
        retVal = 0

        dp = [[0] * (minProfit + 1) for _ in range(n + 1)]
        for i in range(0, n + 1):
            dp[i][0] = 1

        for earn, members in zip(profit, group):
            for j in range(n, members - 1, -1):
                for k in range(minProfit, -1, -1):
                    dp[j][k] = (dp[j][k] + dp[j - members]
                                [max(0, k - earn)]) % self.MODULO
        retVal = dp[n][minProfit]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, minProfit, group, profit in zip([5, 10], [3, 5], [[2, 2], [2, 3, 5]], [[2, 3], [6, 7, 8]]):
            # /* Example
            #  *  Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
            #  *  Output: 2
            #  *
            #  *  Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
            #  *  Output: 7
            #  */
            logging.info(
                "Input: n = %s, minProfit = %s, group = %s, profit = %s", n, minProfit, group, profit)

            retVal = pSolution.profitableSchemes(n, minProfit, group, profit)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
