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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def numSub(self, s: str) -> int:
        retVal = 0

        consecutiveOneCount = 0
        for char in s:
            if char == '1':
                consecutiveOneCount += 1
                continue

            if consecutiveOneCount > 0:
                retVal += ((consecutiveOneCount * (consecutiveOneCount + 1)) // 2)
                retVal %= self.MODULO
                consecutiveOneCount = 0

        if consecutiveOneCount > 0:
            retVal += ((consecutiveOneCount * (consecutiveOneCount + 1)) // 2)
            retVal %= self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["0110111", "101", "111111"]:
            # /* Example
            #  *  Input: s = "0110111"
            #  *  Output: 9
            #  *
            #  *  Input: s = "101"
            #  *  Output: 2
            #  *
            #  *  Input: s = "111111"
            #  *  Output: 21
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.numSub(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
