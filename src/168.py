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
    def convertToTitle(self, columnNumber: int) -> str:
        retVal = ""

        multiple = 26
        while columnNumber > 0:
            columnNumber -= 1
            remainder = columnNumber % multiple
            retVal = chr(remainder + ord("A")) + retVal
            columnNumber //= multiple

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for columnNumber in [1, 28, 701, 2147483647]:
            # /* Example
            # *  Input: columnNumber = 1
            # *  Output: "A"
            # *
            # *  Input: columnNumber = 28
            # *  Output: "AB"
            # *
            # *  Input: columnNumber = 701
            # *  Output: "ZY"
            # *
            # *  Input: columnNumber = 2147483647
            # *  Output: "FXSHRXW"
            # */
            logging.info("Input: columnNumbert = %s", columnNumber)

            retVal = pSolution.convertToTitle(columnNumber)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
