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
    def totalMoney(self, n: int) -> int:
        retVal = 0

        weeks = n // 7
        days = n % 7

        firstWeek = (1 + 7) * 7 // 2
        lastWeek = firstWeek + (weeks-1) * 7
        weeksMoney = (firstWeek + lastWeek) * weeks // 2

        dyasMoney = 0
        monday = 1 + weeks
        for i in range(days):
            dyasMoney += (monday + i)

        retVal = weeksMoney + dyasMoney

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [4, 10, 20]:
            # /* Example
            #  *  Input: n = 4
            #  *  Output: 10
            #  *
            #  *  Input: n = 10
            #  *  Output: 37
            #  *
            #  *  Input: n = 20
            #  *  Output: 96
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.totalMoney(n)
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
