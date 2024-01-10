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
    def minOperations(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        for idx, c in enumerate(s):
            if int(c) != int(idx % 2):
                retVal += 1
        retVal = min(retVal, sSize-retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["0100", "10", "1111"]:
            # /* Example
            #  *  Input: s = "0100"
            #  *  Output: 1
            #  *
            #  *  Input: s = "10"
            #  *  Output: 0
            #  *
            #  *  Input: s = "1111"
            #  *  Output: 2
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.minOperations(s)
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
