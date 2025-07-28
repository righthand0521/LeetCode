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
    def customSortString(self, order: str, s: str) -> str:
        retVal = ""

        val = defaultdict(int)
        for i, ch in enumerate(order):
            val[ch] = 26 - i    # 1 <= order.length <= 26
        retVal = "".join(sorted(s, key=lambda ch: val[ch], reverse=True))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for order, s in zip(["cba", "bcafg"], ["abcd", "abcd"]):
            # /* Example
            #  *  Input:  order = "cba", s = "abcd"
            #  *  Output:  "cbad"
            #  *
            #  *  Input:  order = "bcafg", s = "abcd"
            #  *  Output:  "bcad"
            #  */
            logging.info("Input: order = \"%s\", s = \"%s\"", order, s)

            retVal = pSolution.customSortString(order, s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
