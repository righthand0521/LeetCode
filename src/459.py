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
    def __init__(self):
        self.method = 1

        if self.method == 1:    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
            print("Knuth-Morris-Pratt Algorithm")
        elif self.method == 2:
            print("String Concatenation")
        print()

    def repeatedSubstringPattern(self, s: str) -> bool:
        retVal = False

        if self.method == 1:
            sSize = len(s)

            fail = [-1] * sSize
            for i in range(1, sSize):
                j = fail[i - 1]
                while (j != -1) and (s[j + 1] != s[i]):
                    j = fail[j]

                if s[j + 1] == s[i]:
                    fail[i] = j + 1

            if (fail[sSize - 1] != -1) and (sSize % (sSize - fail[sSize - 1] - 1) == 0):
                retVal = True

        elif self.method == 2:
            doubleString = s + s
            if s in doubleString[1:-1]:
                retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abab", "aba", "abcabcabcabc", "abac", "bb"]:
            # /* Example
            # *  Input: s = "abab"
            # *  Output: true
            # *
            # *  Input: s = "aba"
            # *  Output: false
            # *
            # *  Input: s = "abcabcabcabc"
            # *  Output: true
            # *
            # *  Input: s = "abac"
            # *  Output: false
            # *
            # *  Input: s = "bb"
            # *  Output: true
            # */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.repeatedSubstringPattern(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
