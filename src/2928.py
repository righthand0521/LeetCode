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
    def distributeCandies(self, n: int, limit: int) -> int:
        retVal = 0

        minLimit = min(limit, n)
        for i in range(minLimit + 1):
            if (n - i) > (2 * limit):
                continue
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, limit in zip([5, 3], [2, 3]):
            # /* Example
            #  *  Input: n = 5, limit = 2
            #  *  Output: 3
            #  *
            #  *  Input: n = 3, limit = 3
            #  *  Output: 10
            #  */
            logging.info("Input: n = %s, limit = %s", n, limit)

            retVal = pSolution.distributeCandies(n, limit)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
