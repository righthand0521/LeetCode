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
    def countOdds(self, low: int, high: int) -> int:
        range = high - low + 1
        retVal = range // 2
        if ((range % 2) == 1):
            retVal = retVal+1 if (((low % 2) == 1)
                                  or ((high % 2) == 1)) else retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for low, high in zip([3, 8], [7, 10]):
            # /* Example
            #  *  Input: low = 3, high = 7
            #  *  Output: 3
            #  *
            #  *  Input: low = 8, high = 10
            #  *  Output: 1
            #  */
            logging.info("Input: low = %s, high = %s", low, high)

            retVal = pSolution.countOdds(low, high)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
