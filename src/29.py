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
    def divide(self, dividend: int, divisor: int) -> int:
        quotient = 0

        negative = dividend < 0 or divisor < 0
        if dividend < 0 and divisor < 0:
            negative = 0

        dividend = abs(dividend)
        divisor = abs(divisor)
        for i in range(31, -1, -1):
            if (divisor << i) <= dividend:
                dividend -= (divisor << i)
                quotient += (1 << i)

        if quotient == 2147483648 and negative == 0:
            quotient = 2147483647

        if negative == 1:
            quotient = -1 * quotient

        return quotient


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for dividend, divisor in [[10, 3], [7, -3]]:
            # /* Example
            #  *  Input: dividend = 10, divisor = 3
            #  *  Output: 3
            #  *
            #  *  Input: dividend = 7, divisor = -3
            #  *  Output: -2
            #  */
            logging.info("Input: dividend = %s, divisor = %s", dividend, divisor)

            retVal = pSolution.divide(dividend, divisor)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
