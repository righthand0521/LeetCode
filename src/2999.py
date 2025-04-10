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
    def calculate(self, x: str, s: str, limit: int) -> int:
        retVal = 0

        xSize = len(x)
        sSize = len(s)

        if xSize < sSize:
            return retVal
        elif xSize == sSize:
            if x >= s:
                retVal = 1
            return retVal

        suffix = x[xSize - sSize:]

        preLen = xSize - sSize
        for i in range(preLen):
            if limit < int(x[i]):
                retVal += (limit + 1) ** (preLen - i)
                return retVal
            retVal += int(x[i]) * (limit + 1) ** (preLen - 1 - i)

        if suffix >= s:
            retVal += 1

        return retVal

    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        retVal = 0

        startString = str(start - 1)
        finishString = str(finish)
        retVal = self.calculate(finishString, s, limit) - self.calculate(startString, s, limit)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for start, finish, limit, s in zip([1, 15, 1000], [6000, 215, 2000], [4, 6, 4], ["124", "10", "3000"]):
            # /* Example
            #  *  Input: start = 1, finish = 6000, limit = 4, s = "124"
            #  *  Output: 5
            #  *
            #  *  Input: start = 15, finish = 215, limit = 6, s = "10"
            #  *  Output: 2
            #  *
            #  *  Input: start = 1000, finish = 2000, limit = 4, s = "3000"
            #  *  Output: 0
            #  */
            logging.info("Input: start = %s, finish = %s, limit = %s, s = \"%s\"", start, finish, limit, s)

            retVal = pSolution.numberOfPowerfulInt(start, finish, limit, s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
