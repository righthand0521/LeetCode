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
    def __init__(self) -> None:
        self.kmpStartIdx = -1

    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    def kmp(self, next: List[int], pattern: str) -> None:
        patternSize = len(pattern)

        j = self.kmpStartIdx
        next[0] = j
        for i in range(1, patternSize):
            while (j >= 0) and (pattern[i] != pattern[j + 1]):
                j = next[j]

            if pattern[i] == pattern[j + 1]:
                j += 1

            next[i] = j

    def strStr(self, haystack: str, needle: str) -> int:
        retVal = -1

        needleSize = len(needle)
        if needleSize == 0:
            retVal = 0
            return retVal
        next = [0] * needleSize
        self.kmp(next, needle)

        haystackSize = len(haystack)
        needleIdx = self.kmpStartIdx
        for haystackIdx in range(haystackSize):
            while (needleIdx >= 0) and (haystack[haystackIdx] != needle[needleIdx + 1]):
                needleIdx = next[needleIdx]

            if haystack[haystackIdx] == needle[needleIdx + 1]:
                needleIdx += 1

            if needleIdx == needleSize - 1:
                retVal = haystackIdx - needleSize + 1
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for haystack, needle in zip(["sadbutsad", "leetcode", "mississippi"], ["sad", "leeto", "issip"]):
            # /* Example
            # *  Input: haystack = "sadbutsad", needle = "sad"
            # *  Output: 0
            # *
            # *  Input: haystack = "leetcode", needle = "leeto"
            # *  Output: -1
            # *
            # *  Input: haystack = "mississippi", needle = "issip"
            # *  Output: 4
            # */
            logging.info(
                "Input: haystack = \"%s\", needle = \"%s\"", haystack, needle)

            retVal = pSolution.strStr(haystack, needle)
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
