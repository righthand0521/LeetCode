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
    def rangeBitwiseAnd(self, left: int, right: int) -> int:
        retVal = 0

        shift = 0
        while left < right:
            left >>= 1
            right >>= 1
            shift += 1
        retVal = left << shift

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for left, right in zip([5, 0, 1], [7, 0, 2147483647]):
            # /* Example
            #  *  Input: left = 5, right = 7
            #  *  Output: 4
            #  *
            #  *  Input: left = 0, right = 0
            #  *  Output: 0
            #  *
            #  *  Input: left = 1, right = 2147483647
            #  *  Output: 0
            #  */
            logging.info("Input: left = %s, right = %s", left, right)

            retVal = pSolution.rangeBitwiseAnd(left, right)
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
