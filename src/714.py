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
    def maxProfit(self, prices: List[int], fee: int) -> int:
        retVal = 0

        pricesSize = len(prices)
        dpSell = 0
        dpBuy = -(prices[0])
        for i in range(1, pricesSize):
            tmpSell = max(dpSell, dpBuy + prices[i] - fee)
            tmpBuy = max(dpBuy, dpSell - prices[i])

            dpSell = tmpSell
            dpBuy = tmpBuy
        retVal = dpSell

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for prices, fee in zip([[1, 3, 2, 8, 4, 9], [1, 3, 7, 5, 10, 3]], [2, 3]):
            # /* Example
            #  *  Input: prices = [1,3,2,8,4,9], fee = 2
            #  *  Output: 8
            #  *
            #  *  Input: prices = [1,3,7,5,10,3], fee = 3
            #  *  Output: 6
            #  */
            logging.info("Input: prices = %s, fee = %s", prices, fee)

            retVal = pSolution.maxProfit(prices, fee)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
