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
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:
        retVal = ""

        if numerator % denominator == 0:
            retVal = str(numerator // denominator)
            return retVal

        s = []
        #
        if (numerator < 0) != (denominator < 0):
            s.append('-')
        #
        numerator = abs(numerator)
        denominator = abs(denominator)
        integerPart = numerator // denominator
        s.append(str(integerPart))
        s.append('.')
        #
        indexMap = {}
        remainder = numerator % denominator
        while remainder and remainder not in indexMap:
            indexMap[remainder] = len(s)
            remainder *= 10
            s.append(str(remainder // denominator))
            remainder %= denominator
        if remainder:
            insertIndex = indexMap[remainder]
            s.insert(insertIndex, '(')
            s.append(')')
        #
        retVal = ''.join(s)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for numerator, denominator in [[1, 2], [2, 1], [4, 333]]:
            # /* Example
            #  *  Input: numerator = 1, denominator = 2
            #  *  Output: "0.5"
            #  *
            #  *  Input: numerator = 2, denominator = 1
            #  *  Output: "2"
            #  *
            #  *  Input: numerator = 4, denominator = 333
            #  *  Output: "0.(012)"
            #  */
            logging.info("Input: numerator = %s, denominator = %s", numerator, denominator)

            retVal = pSolution.fractionToDecimal(numerator, denominator)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
