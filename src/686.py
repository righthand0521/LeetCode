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
    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    def kmp(self, next: List[int], pattern: str) -> None:
        patternSize = len(pattern)

        j = 0
        for i in range(1, patternSize):
            while (j > 0) and (pattern[i] != pattern[j]):
                j = next[j-1]

            if pattern[i] == pattern[j]:
                j += 1

            next[i] = j

    def strstr(self, haystack: str, needle: str) -> int:
        retVal = -1

        needleSize = len(needle)
        if needleSize == 0:
            retVal = 0
            return retVal
        next = [0] * needleSize
        self.kmp(next, needle)

        haystackSize = len(haystack)
        haystackIdx = 0
        needleIdx = 0
        while haystackIdx - needleIdx < haystackSize:
            while (needleIdx > 0) and (haystack[haystackIdx % haystackSize] != needle[needleIdx]):
                needleIdx = next[needleIdx - 1]

            if haystack[haystackIdx % haystackSize] == needle[needleIdx]:
                needleIdx += 1

            if needleIdx == needleSize:
                retVal = haystackIdx - needleSize + 1
                break

            haystackIdx += 1

        return retVal

    def repeatedStringMatch(self, a: str, b: str) -> int:
        retVal = -1

        aSize = len(a)
        bSize = len(b)
        index = self.strstr(a, b)
        if index == -1:
            retVal = -1
        elif aSize - index >= bSize:
            retVal = 1
        else:
            retVal = (bSize + index - aSize - 1) // aSize + 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for a, b in zip(["abcd", "a", "aaac"], ["cdabcdab", "aa", "aac"]):
            # /* Example
            # *  Input: a = "abcd", b = "cdabcdab"
            # *  Output: 3
            # *
            # *  Input: a = "a", b = "aa"
            # *  Output: 2
            # *
            # *  Input: a = "aaac", b = "aac"
            # *  Output: 1
            # */
            logging.info("Input: a = \"%s\", b = \"%s\"", a, b)

            retVal = pSolution.repeatedStringMatch(a, b)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
