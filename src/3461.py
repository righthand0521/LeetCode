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


# https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/solutions/6457845/python-check-mod2-and-mod5/
class Solution:
    def cal(self, a, mod) -> tuple[int, int]:
        retVal = (0, 0)

        count = 0
        while (a > 0) and (a % mod == 0):
            count += 1
            a //= mod
        retVal = (a % mod, count)

        return retVal

    def test(self, s: str, mod) -> bool:
        retVal = True

        sSize = len(s)

        res = 0
        r = 1
        c = 0
        for i in range(sSize - 1):
            if c == 0:
                res += (r * (int(s[i]) - int(s[i + 1])))

            rr, cc = self.cal(sSize - 2 - i, mod)
            r = r * rr % mod
            c += cc

            rr, cc = self.cal(i + 1, mod)
            r = r * pow(rr, mod - 2, mod) % mod
            c -= cc

        retVal = (res % mod == 0)

        return retVal

    def hasSameDigits(self, s: str) -> bool:
        retVal = True

        retVal = self.test(s, 2) and self.test(s, 5)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["3902", "34789"]:
            # /* Example
            #  *  Input: s = "3902"
            #  *  Output: true
            #  *
            #  *  Input: s = "34789"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.hasSameDigits(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
