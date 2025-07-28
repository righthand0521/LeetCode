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
    def CanPartition(self, num, target):
        retVal = False

        if (target < 0) or (target > num):
            return retVal
        elif num == target:
            retVal = True
            return retVal
        retVal = self.CanPartition(num // 10, target - num % 10)
        retVal = retVal or self.CanPartition(num // 100, target - num % 100)
        retVal = retVal or self.CanPartition(num // 1000, target - num % 1000)

        return retVal

    def punishmentNumber(self, n: int) -> int:
        retVal = 0

        for currentNum in range(1, n + 1):
            squareNum = currentNum * currentNum
            if self.CanPartition(squareNum, currentNum):
                retVal += squareNum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [10, 37]:
            # /* Example
            #  *  Input: n = 10
            #  *  Output: 182
            #  *
            #  *  Input: n = 37
            #  *  Output: 1478
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.punishmentNumber(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
