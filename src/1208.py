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
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        retVal = 0

        sSize = len(s)

        cost = 0
        start = 0
        end = 0
        for end in range(sSize):
            cost += abs(ord(s[end]) - ord(t[end]))
            while cost > maxCost:
                cost -= abs(ord(s[start]) - ord(t[start]))
                start += 1
            retVal = max(retVal, end-start+1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, t, maxCost in zip(["abcd", "abcd", "abcd"], ["bcdf", "cdef", "acde"], [3, 3, 0]):
            # /* Example
            #  *  Input: s = "abcd", t = "bcdf", maxCost = 3
            #  *  Output: 3
            #  *
            #  *  Input: s = "abcd", t = "cdef", maxCost = 3
            #  *  Output: 1
            #  *
            #  *  Input: s = "abcd", t = "acde", maxCost = 0
            #  *  Output: 1
            #  */
            logging.info("Input: s = \"%s\", t = \"%s\", maxCost = %s", s, t, maxCost)

            retVal = pSolution.equalSubstring(s, t, maxCost)
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
