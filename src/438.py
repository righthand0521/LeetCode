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
    def __init__(self) -> None:
        self.letters = 26  # s and p consist of lowercase English letters.

    def findAnagrams(self, s: str, p: str) -> List[int]:
        retVal = []

        sSize = len(s)
        pSize = len(p)
        if sSize < pSize:
            return retVal

        sCount = [0] * self.letters
        pCount = [0] * self.letters
        for i in range(pSize):
            sCount[ord(s[i]) - ord('a')] += 1
            pCount[ord(p[i]) - ord('a')] += 1
        if sCount == pCount:
            retVal.append(0)

        for i in range(pSize, sSize):
            sCount[ord(s[i]) - ord('a')] += 1
            sCount[ord(s[i - pSize]) - ord('a')] -= 1
            if sCount == pCount:
                retVal.append(i - pSize + 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, p in zip(["cbaebabacd", "abab"], ["abc", "ab"]):
            # /* Example
            #  *  Input: s = "cbaebabacd", p = "abc"
            #  *  Output: [0,6]
            #  *
            #  *  Input: s = "abab", p = "ab"
            #  *  Output: [0,1,2]
            #  */
            logging.info("Input: s = \"%s\", p = \"%s\"", s, p)

            retVal = pSolution.findAnagrams(s, p)
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
