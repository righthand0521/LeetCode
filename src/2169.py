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
    def countOperations(self, num1: int, num2: int) -> int:
        retVal = 0

        while (num1 != 0) and (num2 != 0):
            retVal += (num1 // num2)
            num1 %= num2
            num1, num2 = num2, num1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num1, num2 in [[2, 3], [10, 10]]:
            # /* Example
            #  *  Input: num1 = 2, num2 = 3
            #  *  Output: 3
            #  *
            #  *  Input: num1 = 10, num2 = 10
            #  *  Output: 1
            #  */
            logging.info("Input: num1 = %s, num2 = %s", num1, num2)

            retVal = pSolution.countOperations(num1, num2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
