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
        buy1 = -(prices[0])
        sell1 = 0
        buy2 = -(prices[0])
        sell2 = 0
        for i in range(1, pricesSize):
            dpBuy1 = max(buy1, -(prices[i]))
            dpSell1 = max(sell1, buy1 + prices[i])
            dpBuy2 = max(buy2, sell1 - prices[i])
            dpSell2 = max(sell2, buy2 + prices[i])

            buy1 = dpBuy1
            sell1 = dpSell1
            buy2 = dpBuy2
            sell2 = dpSell2

        retVal = sell2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for prices in [[3, 3, 5, 0, 0, 3, 1, 4], [1, 2, 3, 4, 5], [7, 6, 4, 3, 1]]:
            # /* Example
            #  *  Input: prices = [3,3,5,0,0,3,1,4]
            #  *  Output: 6
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
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
