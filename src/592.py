import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import gcd
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
    def fractionAddition(self, expression: str) -> str:
        retVal = "0/1"

        expressionSize = len(expression)

        numerator = 0
        denominator = 1
        i = 0
        while i < expressionSize:
            sign = 1
            x = 0
            if (expression[i] == '-') or (expression[i] == '+'):
                if expression[i] == '-':
                    sign = -1
                i += 1
            while (i < expressionSize) and (expression[i].isdigit()):
                x = x * 10 + int(expression[i])
                i += 1
            x = sign * x
            i += 1

            y = 0
            while (i < expressionSize) and (expression[i].isdigit()):
                y = y * 10 + int(expression[i])
                i += 1

            numerator = numerator * y + x * denominator
            denominator *= y

        if numerator != 0:
            greatestCommonDivisor = gcd(abs(numerator), denominator)
            numerator //= greatestCommonDivisor
            denominator //= greatestCommonDivisor
            retVal = str(numerator) + "/" + str(denominator)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for expression in ["-1/2+1/2", "-1/2+1/2+1/3", "1/3-1/2"]:
            # /* Example
            #  *  Input: expression = "-1/2+1/2"
            #  *  Output: "0/1"
            #  *
            #  *  Input: expression = "-1/2+1/2+1/3"
            #  *  Output: "1/3"
            #  *
            #  *  Input: expression = "1/3-1/2"
            #  *  Output: "-1/6"
            #  */
            logging.info("Input: expression = \"%s\"", expression)

            retVal = pSolution.fractionAddition(expression)
            logging.info("Output: \"%s\"", retVal)

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
