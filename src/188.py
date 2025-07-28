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
    def maxProfit(self, k: int, prices: List[int]) -> int:
        retVal = 0

        buy = [-(prices[0])] * (k+1)
        sell = [0] * (k+1)

        pricesSize = len(prices)
        for i in range(1, pricesSize):
            dpBuy = [0] * (k+1)
            dpSell = [0] * (k+1)
            for j in range(1, k+1):
                dpBuy[j] = max(buy[j], sell[j - 1] - prices[i])
                dpSell[j] = max(sell[j], buy[j] + prices[i])

            for j in range(1, k+1):
                buy[j] = dpBuy[j]
                sell[j] = dpSell[j]
        retVal = sell[k]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for k, prices in zip([2, 2], [[2, 4, 1], [3, 2, 6, 5, 0, 3]]):
            # /* Example
            #  *  Input: k = 2, prices = [2,4,1]
            #  *  Output: 2
            #  *
            #  *  Input: k = 2, prices = [3,2,6,5,0,3]
            #  *  Output: 7
            #  */
            logging.info("Input: k = %s, prices = %s", k, prices)

            retVal = pSolution.maxProfit(k, prices)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
