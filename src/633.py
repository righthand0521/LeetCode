import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import sqrt
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
    def judgeSquareSum(self, c: int) -> bool:
        retVal = False

        left = 0
        right = int(sqrt(c))
        while left <= right:
            sum = (left * left) + (right * right)
            if sum == c:
                retVal = True
                break
            elif sum > c:
                right -= 1
            else:
                left += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for c in [5, 3]:
            # /* Example
            #  *  Input: c = 5
            #  *  Output: true
            #  *
            #  *  Input: c = 3
            #  *  Output: false
            #  */
            logging.info("Input: c = %s", c)

            retVal = pSolution.judgeSquareSum(c)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
