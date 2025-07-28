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
    def bitwiseComplement(self, n: int) -> int:
        retVal = n

        # 0 <= n < 10^9
        if n == 0:
            retVal = 1
            return retVal

        i = 31
        while retVal & (1 << i) == 0:
            i -= 1

        while i >= 0:
            retVal ^= (1 << i)
            i -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [5, 7, 10]:
            # /* Example
            #  *  Input: n = 5
            #  *  Output: 2
            #  *
            #  *  Input: n = 7
            #  *  Output: 0
            #  *
            #  *  Input: n = 10
            #  *  Output: 5
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.bitwiseComplement(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
