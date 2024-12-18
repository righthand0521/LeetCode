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
    def finalPrices(self, prices: List[int]) -> List[int]:
        retVal = prices

        monotonicStack = deque()
        priceSize = len(prices)
        for i in range(priceSize):
            # Process items that can be discounted by current price
            while monotonicStack and (prices[monotonicStack[-1]] >= prices[i]):
                # Apply discount to previous item using current price
                retVal[monotonicStack.pop()] -= prices[i]

            # Add current index to monotonicStack
            monotonicStack.append(i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for prices in [[8, 4, 6, 2, 3], [1, 2, 3, 4, 5], [10, 1, 1, 6]]:
            # /* Example
            #  *  Input: prices = [8,4,6,2,3]
            #  *  Output: [4,2,4,2,3]
            #  *
            #  *  Input: prices = [1,2,3,4,5]
            #  *  Output: [1,2,3,4,5]
            #  *
            #  *  Input: prices = [10,1,1,6]
            #  *  Output: [9,0,1,6]
            #  */
            logging.info("Input: prices = %s", prices)

            retVal = pSolution.finalPrices(prices)
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
