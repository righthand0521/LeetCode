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
    @cache
    def dfs(self, maxChoosableInteger: int, desiredTotal: int, usedNumbers: int, currentTotal: int) -> bool:
        retVal = False

        for i in range(maxChoosableInteger):
            if (usedNumbers >> i) & 1 != 0:
                continue

            if currentTotal + i + 1 >= desiredTotal:
                retVal = True
                break

            if self.dfs(maxChoosableInteger, desiredTotal, usedNumbers | (1 << i), currentTotal + i + 1) == False:
                retVal = True
                break

        return retVal

    def canIWin(self, maxChoosableInteger: int, desiredTotal: int) -> bool:
        retVal = False

        if ((1+maxChoosableInteger)*maxChoosableInteger) // 2 < desiredTotal:
            return retVal

        retVal = self.dfs(maxChoosableInteger, desiredTotal, 0, 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for maxChoosableInteger, desiredTotal in zip([10, 10, 10], [11, 0, 1]):
            # /* Example
            #  *  Input: maxChoosableInteger = 10, desiredTotal = 11
            #  *  Output: false
            #  *
            #  *  Input: maxChoosableInteger = 10, desiredTotal = 0
            #  *  Output: true
            #  *
            #  *  Input: maxChoosableInteger = 10, desiredTotal = 1
            #  *  Output: true
            #  */
            logging.info("Input: maxChoosableInteger = %s, desiredTotal = %s", maxChoosableInteger, desiredTotal)

            retVal = pSolution.canIWin(maxChoosableInteger, desiredTotal)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
