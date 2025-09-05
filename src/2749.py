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
    def makeTheIntegerZero(self, num1: int, num2: int) -> int:
        retVal = -1

        k = 1
        while True:
            x = num1 - num2 * k
            if x < k:
                break
            elif k >= x.bit_count():
                retVal = k
                break
            k += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num1, num2 in [(3, -2), (5, 7)]:
            # /* Example
            #  *  Input: num1 = 3, num2 = -2
            #  *  Output: 3
            #  *
            #  *  Input: num1 = 5, num2 = 7
            #  *  Output: -1
            #  */
            logging.info("Input: num1 = %s, num2 = %s", num1, num2)

            retVal = pSolution.makeTheIntegerZero(num1, num2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
