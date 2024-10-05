import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import gcd
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
        self.letters = 26  # // s1 and s2 consist of lowercase English letters.

    def checkInclusion(self, s1: str, s2: str) -> bool:
        retVal = False

        s1Size = len(s1)
        s2Size = len(s2)
        if s2Size < s1Size:
            return retVal

        count1 = [0] * self.letters
        count2 = [0] * self.letters

        for i in range(s1Size):
            count1[ord(s1[i]) - ord('a')] += 1
            count2[ord(s2[i]) - ord('a')] += 1
        if count1 == count2:
            retVal = True
            return retVal

        for i in range(s1Size, s2Size):
            count2[ord(s2[i]) - ord('a')] += 1
            count2[ord(s2[i-s1Size]) - ord('a')] -= 1
            if count1 == count2:
                retVal = True
                return retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s1, s2 in zip(["ab", "ab"], ["eidbaooo", "eidboaoo"]):
            # /* Example
            #  *  Input: s1 = "ab", s2 = "eidbaooo"
            #  *  Output: true
            #  *
            #  *  Input: s1 = "ab", s2 = "eidboaoo"
            #  *  Output: false
            #  */
            logging.info("Input: s1 = \"%s\", s2 = \"%s\"", s1, s2)

            retVal = pSolution.checkInclusion(s1, s2)
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
