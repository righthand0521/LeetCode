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
    def maxProfit(self, prices: List[int]) -> int:
        retVal = 0

        pricesSize = len(prices)
        buy = -(prices[0])
        sell = 0
        for i in range(1, pricesSize):
            dpBuy = max(buy, sell - prices[i])
            dpSell = max(sell, buy + prices[i])

            buy = dpBuy
            sell = dpSell

        retVal = sell

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for prices in [[7, 1, 5, 3, 6, 4], [1, 2, 3, 4, 5], [7, 6, 4, 3, 1]]:
            # /* Example
            #  *  Input: prices = [7,1,5,3,6,4]
            #  *  Output: 7
            #  *
            #  *  Input: prices = [1,2,3,4,5]
            #  *  Output: 4
            #  *
            #  *  Input: prices = [7,6,4,3,1]
            #  *  Output: 0
            #  */
            logging.info("Input: prices = %s", prices)

            retVal = pSolution.maxProfit(prices)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
