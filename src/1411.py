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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def numOfWays(self, n: int) -> int:
        retVal = 0

        fi0 = 6
        fi1 = 6
        for _ in range(2, n + 1):
            fi0New = (2 * fi0 + 2 * fi1) % self.MODULO
            fi1New = (2 * fi0 + 3 * fi1) % self.MODULO
            fi0 = fi0New
            fi1 = fi1New
        retVal = (fi0 + fi1) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [1, 5000]:
            # /* Example
            #  *  Input: n = 1
            #  *  Output: 12
            #  *
            #  *  Input: n = 5000
            #  *  Output: 30228214
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.numOfWays(n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
