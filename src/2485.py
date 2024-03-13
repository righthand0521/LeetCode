import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import sqrt


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
    def pivotInteger(self, n: int) -> int:
        retVal = -1

        # 1 + 2 + ... + x = x + ... + n
        # => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
        # => 2 * x^2 = n^2 + n
        # => x = ((n^2 + n) / 2)^(1/2)
        # => x = ((n * (n+1) / 2))^(1/2)
        sum = n * (n + 1) // 2
        x = int(sqrt(sum))
        if x * x == sum:
            retVal = x

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [8, 1, 4]:
            # /* Example
            #  *  Input: n = 8
            #  *  Output: 6
            #  *
            #  *  Input: n = 1
            #  *  Output: 1
            #  *
            #  *  Input: n = 4
            #  *  Output: -1
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.pivotInteger(n)
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
