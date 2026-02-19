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
    def countBinarySubstrings(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        current = 1
        previous = 0
        for i in range(1, sSize):
            if s[i] != s[i - 1]:
                retVal += min(previous, current)
                previous = current
                current = 1
            else:
                current += 1
        retVal += min(previous, current)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["00110011", "10101"]:
            # /* Example
            #  *  Input: s = "00110011"
            #  *  Output: 6
            #  *
            #  *  Input: s = "10101"
            #  *  Output: 4
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.countBinarySubstrings(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
