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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def countHomogenous(self, s: str) -> int:
        retVal = 1  # 1 <= s.length <= 10^5

        sSize = len(s)
        homogenous = 1
        for i in range(1, sSize):
            if s[i-1] == s[i]:
                homogenous += 1
            else:
                homogenous = 1

            retVal += homogenous
            retVal %= self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abbcccaa", "xy", "zzzzz"]:
            # /* Example
            #  *  Input: s = "abbcccaa"
            #  *  Output: 13
            #  *
            #  *  Input: s = "xy"
            #  *  Output: 2
            #  *
            #  *  Input: s = "zzzzz"
            #  *  Output: 15
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.countHomogenous(s)
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
