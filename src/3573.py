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
    def maximumProfit(self, prices: List[int], k: int) -> int:
        retVal = 0

        pricesSize = len(prices)

        dp = [[0] * 3 for _ in range(k + 1)]
        for j in range(1, k + 1):
            dp[j][1] = -prices[0]
            dp[j][2] = prices[0]

        for i in range(1, pricesSize):
            for j in range(k, 0, -1):
                dp[j][0] = max(dp[j][0], max(dp[j][1] + prices[i], dp[j][2] - prices[i]))
                dp[j][1] = max(dp[j][1], dp[j - 1][0] - prices[i])
                dp[j][2] = max(dp[j][2], dp[j - 1][0] + prices[i])
        retVal = dp[k][0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for prices, k in [[1, 7, 9, 8, 2], 2], [[12, 16, 19, 19, 8, 1, 19, 13, 9], 3]:
            # /* Example
            #  *  Input: prices = [1,7,9,8,2], k = 2
            #  *  Output: 14
            #  *
            #  *  Input: prices = [12,16,19,19,8,1,19,13,9], k = 3
            #  *  Output: 36
            #  */
            logging.info("Input: prices = %s, k = %s", prices, k)

            retVal = pSolution.maximumProfit(prices, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
