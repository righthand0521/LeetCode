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
    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    def kmp(self, s: str) -> List[int]:
        retVal = []

        sSize = len(s)

        retVal = [0] * sSize
        length = 0
        for i in range(1, sSize):
            while (length > 0) and (s[i] != s[length]):
                length = retVal[length - 1]

            if s[i] == s[length]:
                length += 1

            retVal[i] = length

        return retVal

    def shortestPalindrome(self, s: str) -> str:
        retVal = s

        reversedString = s[::-1]
        combinedString = s + "#" + reversedString

        prefixTable = self.kmp(combinedString)
        palindromeLength = prefixTable[-1]

        suffix = reversedString[: len(s) - palindromeLength]
        retVal = suffix + s

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aacecaaa", "abcd"]:
            # /* Example
            #  *  Input: s = "aacecaaa"
            #  *  Output: "aaacecaaa"
            #  *
            #  *  Input: s = "abcd"
            #  *  Output: "dcbabcd"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.shortestPalindrome(s)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
