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
    def kthGrammar(self, n: int, k: int) -> int:
        retVal = 0

        if 1 == 0:  # Recursion
            # 0
            # 0 1
            # 0 1 1 0
            # 0 1 1 0 1 0 0 1
            # 0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0
            if k == 1:
                return retVal
            if k > (1 << (n - 2)):
                retVal = 1 ^ self.kthGrammar(n - 1, k - (1 << (n - 2)))
                return retVal
            retVal = self.kthGrammar(n - 1, k)
        else:   # Bit Manipulation: 0->01, 1-> 10.
            # +-------------------------------+
            # | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
            # +-------------------------------+
            # | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |
            # +-------------------------------+
            # | 0 | 1 |   |   |   |   |   |   |
            # |   | 1 | 1 | 0 |   |   |   |   |
            # |   |   | 1 |   | 1 | 0 |   |   |
            # |   |   |   | 0 |   |   | 0 | 1 |
            # +-------------------------------+
            # retVal = (k - 1).bit_count() & 1
            k -= 1
            while k:
                k &= (k - 1)
                retVal ^= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([1, 2, 2], [1, 1, 2]):
            # /* Example
            #  *  Input: n = 1, k = 1
            #  *  Output: 0
            #  *
            #  *  Input: n = 2, k = 1
            #  *  Output: 0
            #  *
            #  *  Input: n = 2, k = 2
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.kthGrammar(n, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
