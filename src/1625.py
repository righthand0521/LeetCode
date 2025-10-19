import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from math import gcd


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
    def __init__(self) -> None:
        self.sSize = 0

    def add(self, a: int, t: str, start: int) -> str:
        retVal = None

        original = int(t[start])
        min_val, times = 10, 0
        for i in range(10):
            added = (original + i * a) % 10
            if added < min_val:
                min_val = added
                times = i

        t_list = list(t)
        for i in range(start, self.sSize, 2):
            t_list[i] = str((int(t_list[i]) + times * a) % 10)
        retVal = "".join(t_list)

        return retVal

    def findLexSmallestString(self, s: str, a: int, b: int) -> str:
        retVal = s

        self.sSize = len(s)

        s = s + s
        g = gcd(b, self.sSize)
        for i in range(0, self.sSize, g):
            t = s[i: i + self.sSize]
            t = self.add(a, t, 1)
            if b % 2:
                t = self.add(a, t, 0)
            if t < retVal:
                retVal = t

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, a, b in [["5525", 9, 2], ["74", 5, 1], ["0011", 4, 2]]:
            # /* Example
            #  *  Input: s = "5525", a = 9, b = 2
            #  *  Output: "2050"
            #  *
            #  *  Input: s = "74", a = 5, b = 1
            #  *  Output: "24"
            #  *
            #  *  Input: s = "0011", a = 4, b = 2
            #  *  Output: "0011"
            #  */
            logging.info("Input: s = \"%s\", a = %s, b = %s", s, a, b)

            retVal = pSolution.findLexSmallestString(s, a, b)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
