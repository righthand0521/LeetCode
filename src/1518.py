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
    def numWaterBottles(self, numBottles: int, numExchange: int) -> int:
        retVal = 0

        consumedBottles = 0
        while numBottles >= numExchange:
            times = numBottles // numExchange
            consumedBottles += (numExchange * times)
            numBottles -= (numExchange * times)
            numBottles += times
        retVal = consumedBottles + numBottles

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for numBottles, numExchange in zip([9, 15], [3, 4]):
            # /* Example
            #  *  Input: numBottles = 9, numExchange = 3
            #  *  Output: 13
            #  *
            #  *  Input: numBottles = 15, numExchange = 4
            #  *  Output: 19
            #  */
            logging.info("Input: numBottles = %s, numExchange = %s", numBottles, numExchange)

            retVal = pSolution.numWaterBottles(numBottles, numExchange)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
