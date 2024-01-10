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
    def reverseStr(self, s: str, k: int) -> str:
        retVal = ""

        sSize = len(s)
        for i in range(0, sSize, 2 * k):
            pStr1 = s[i: i + k]
            pStr2 = s[i + k: i + 2 * k]
            retVal += (pStr1[::-1] + pStr2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["abcdefg", "abcd"], [2, 2]):
            # /* Example
            #  *  Input: s = "abcdefg", k = 2
            #  *  Output: "bacdfeg"
            #  *
            #  *  Input: s = "abcd", k = 2
            #  *  Output: "bacd"
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.reverseStr(s, k)
            logging.info("Output: \"%s\"", retVal)

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
