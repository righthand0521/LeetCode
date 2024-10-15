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
    def minimumSteps(self, s: str) -> int:
        retVal = 0

        sum = 0
        for c in s:
            if c == '1':
                sum += 1
            else:
                retVal += sum

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["101", "100", "0111"]:
            # /* Example
            #  *  Input: s = "101"
            #  *  Output: 1
            #  *
            #  *  Input: s = "100"
            #  *  Output: 2
            #  *
            #  *  Input: s = "0111"
            #  *  Output: 0
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.minimumSteps(s)
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
