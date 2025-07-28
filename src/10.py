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
    def matches(self, s: str, p: str, i: int, j: int) -> bool:
        retVal = False

        if i == 0:
            retVal = False
        elif p[j - 1] == '.':
            retVal = True
        else:
            retVal = (s[i - 1] == p[j - 1])

        return retVal

    def isMatch(self, s: str, p: str) -> bool:
        retVal = False

        sSize = len(s)
        pSize = len(p)
        dp = [[False] * (pSize + 1) for _ in range(sSize + 1)]
        dp[0][0] = True
        for i in range(sSize + 1):
            for j in range(1, pSize + 1):
                if p[j - 1] == '*':
                    dp[i][j] |= dp[i][j - 2]
                    if self.matches(s, p, i, j - 1) == True:
                        dp[i][j] |= dp[i - 1][j]
                else:
                    if self.matches(s, p, i, j) == True:
                        dp[i][j] |= dp[i - 1][j - 1]
        retVal = dp[sSize][pSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, p in [["aa", "a"], ["aa", "a*"], ["ab", ".*"]]:
            # /* Example
            #  *  Input: s = "aa", p = "a"
            #  *  Output: false
            #  *
            #  *  Input: s = "aa", p = "a*"
            #  *  Output: true
            #  *
            #  *  Input: s = "ab", p = ".*"
            #  *  Output: true
            #  */
            logging.info("Input: s = \"%s\", p = \"%s\"", s, p)

            retVal = pSolution.isMatch(s, p)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
