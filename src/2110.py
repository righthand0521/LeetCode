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
    def getDescentPeriods(self, prices: List[int]) -> int:
        retVal = 1  # total number of smooth descending periods, initial value is dp[0]

        pricesSize = len(prices)
        prev = 1  # total number of smooth descending periods ending with the previous element, initial value is dp[0]
        # traverse the array starting from 1, and update prev and the total retVal according to the recurrence relation
        for i in range(1, pricesSize):
            if prices[i] == prices[i - 1] - 1:
                prev += 1
            else:
                prev = 1

            retVal += prev

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for prices in [[3, 2, 1, 4], [8, 6, 7, 7], [1]]:
            # /* Example
            #  *  Input: prices = [3,2,1,4]
            #  *  Output: 7
            #  *
            #  *  Input: prices = [8,6,7,7]
            #  *  Output: 4
            #  *
            #  *  Input: prices = [1]
            #  *  Output: 1
            #  */
            logging.info("Input: prices = %s", prices)

            retVal = pSolution.getDescentPeriods(prices)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
