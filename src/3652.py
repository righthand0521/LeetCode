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
    def maxProfit(self, prices: List[int], strategy: List[int], k: int) -> int:
        retVal = 0

        pricesSize = len(prices)

        profitSum = [0] * (pricesSize + 1)
        priceSum = [0] * (pricesSize + 1)
        for i in range(pricesSize):
            profitSum[i + 1] = profitSum[i] + prices[i] * strategy[i]
            priceSum[i + 1] = priceSum[i] + prices[i]
        retVal = profitSum[pricesSize]

        for i in range(k - 1, pricesSize):
            leftProfit = profitSum[i - k + 1]
            rightProfit = profitSum[pricesSize] - profitSum[i + 1]
            changeProfit = priceSum[i + 1] - priceSum[i - k // 2 + 1]
            retVal = max(retVal, leftProfit + changeProfit + rightProfit)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for prices, strategy, k in [[4, 2, 8], [-1, 0, 1], 2], [[5, 4, 3], [1, 1, 0], 2]:
            # /* Example
            #  *  Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
            #  *  Output: 10
            #  *
            #  *  Input: prices = [5,4,3], strategy = [1,1,0], k = 2
            #  *  Output: 9
            #  */
            logging.info("Input: prices = %s, strategy = %s, k = %s", prices, strategy, k)

            retVal = pSolution.maxProfit(prices, strategy, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
