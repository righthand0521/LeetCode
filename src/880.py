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
    def decodeAtIndex(self, s: str, k: int) -> str:
        retVal = ""

        size = 0
        for c in s:
            if c.isdigit():
                size *= int(c)
            else:
                size += 1

        for c in reversed(s):
            k %= size
            if k == 0 and c.isalpha():
                retVal = c
                break

            if c.isdigit():
                size /= int(c)
            else:
                size -= 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["leet2code3", "ha22", "a2345678999999999999999"], [10, 5, 1]):
            # /* Example
            #  *  Input: s = "leet2code3", k = 10
            #  *  Output: "o"
            #  *
            #  *  Input: s = "ha22", k = 5
            #  *  Output: "h"
            #  *
            #  *  Input: s = "a2345678999999999999999", k = 1
            #  *  Output: "a"
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.decodeAtIndex(s, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
