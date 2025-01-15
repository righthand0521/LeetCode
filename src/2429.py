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
    def isSet(self, x: int, bit: int) -> bool:
        retVal = ((x & (1 << bit)) != 0)

        return retVal

    def setBit(self, x: int, bit: int) -> int:
        retVal = (x | (1 << bit))

        return retVal

    def unsetBit(self, x: int, bit: int) -> int:
        retVal = (x & ~(1 << bit))

        return retVal

    def minimizeXor(self, num1: int, num2: int) -> int:
        retVal = num1

        targetSetBitsCount = bin(num2).count("1")
        setBitsCount = bin(retVal).count("1")
        currentBit = 0

        while setBitsCount < targetSetBitsCount:
            if self.isSet(retVal, currentBit) == False:
                retVal = self.setBit(retVal, currentBit)
                setBitsCount += 1
            currentBit += 1

        while setBitsCount > targetSetBitsCount:
            if self.isSet(retVal, currentBit) == True:
                retVal = self.unsetBit(retVal, currentBit)
                setBitsCount -= 1
            currentBit += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num1, num2 in zip([3, 1], [5, 12]):
            # /* Example
            #  *  Input: num1 = 3, num2 = 5
            #  *  Output: 3
            #  *
            #  *  Input: num1 = 1, num2 = 12
            #  *  Output: 3
            #  */
            logging.info("Input: num1 = %s, num2 = %s", num1, num2)

            retVal = pSolution.minimizeXor(num1, num2)
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
