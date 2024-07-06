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
    def passThePillow(self, n: int, time: int) -> int:
        retVal = 0

        direction = time // (n-1)
        index = time % (n-1)
        if direction % 2 == 0:
            retVal = index + 1
        elif direction % 2 == 1:
            retVal = n - index

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, times in zip([4, 3], [5, 2]):
            # /* Example
            #  *  Input: n = 4, time = 5
            #  *  Output: 2
            #  *
            #  *  Input: n = 3, time = 2
            #  *  Output: 3
            #  */
            logging.info("Input: n = %s, time = %s", n, times)

            retVal = pSolution.passThePillow(n, times)
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
