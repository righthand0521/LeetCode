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
    def myPow(self, x: float, n: int) -> float:
        retVal = 1

        # /* https://en.wikipedia.org/wiki/Exponentiation_by_squaring
        #  *
        #  * func binaryExp(x, n):
        #  *  if n == 0: return 1.0
        #  *  if n < 0: return 1.0 / binaryExp(x, -n)
        #  *  // Binary exponentiation steps.
        #  *  if n is odd: return x * binaryExp(x * x, (n - 1) / 2)
        #  *  otherwise: return binaryExp(x * x, n / 2)
        #  */

        if (x == 0) or (x == 1):
            retVal = x
            return retVal
        elif x == -1:
            retVal = 1 if n % 2 == 0 else -1
            return retVal

        x = x if n > 0 else 1/x

        times = abs(n)
        while (times > 0):
            if times % 2 == 1:
                retVal *= x
                times -= 1
            if retVal == 0:
                break

            x *= x
            times = times >> 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for x, n in zip([2.00000, 2.10000, 2.00000], [10, 3, -2]):
            # /* Example
            #  *  Input: x = 2.00000, n = 10
            #  *  Output: 1024.00000
            #  *
            #  *  Input: x = 2.10000, n = 3
            #  *  Output: 9.26100
            #  *
            #  *  Input: x = 2.00000, n = -2
            #  *  Output: 0.25000
            #  */
            logging.info("Input: x = %s, n = %s", x, n)

            retVal = pSolution.myPow(x, n)
            logging.info("Output: %.5f", retVal)

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
