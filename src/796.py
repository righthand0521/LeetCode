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
    def rotateString(self, s: str, goal: str) -> bool:
        retVal = False

        if len(s) != len(goal):
            return retVal

        if goal in s+s:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, goal in zip(["abcde", "abcde"], ["cdeab", "abced"]):
            # /* Example
            #  *  Input: s = "abcde", goal = "cdeab"
            #  *  Output: true
            #  *
            #  *  Input: s = "abcde", goal = "abced"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\", goal = \"%s\"", s, goal)

            retVal = pSolution.rotateString(s, goal)
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
