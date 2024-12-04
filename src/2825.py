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
    def canMakeSubsequence(self, str1: str, str2: str) -> bool:
        retVal = False

        str1Size = len(str1)
        str2Size = len(str2)

        str2Index = 0
        for str1Index in range(str1Size):
            if str2Index >= str2Size:
                break
            elif (str1[str1Index] == str2[str2Index]):
                str2Index += 1
            elif (ord(str1[str1Index]) + 1 == ord(str2[str2Index])):
                str2Index += 1
            elif (ord(str1[str1Index]) - 25 == ord(str2[str2Index])):
                str2Index += 1

        if str2Index == str2Size:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for str1, str2 in zip(["abc", "zc", "ab"], ["ad", "ad", "d"]):
            # /* Example
            #  *  Input: str1 = "abc", str2 = "ad"
            #  *  Output: true
            #  *
            #  *  Input: str1 = "zc", str2 = "ad"
            #  *  Output: true
            #  *
            #  *  Input: str1 = "ab", str2 = "d"
            #  *  Output: false
            #  */
            logging.info("Input: str1 = \"%s\", str2 = \"%s\"", str1, str2)

            retVal = pSolution.canMakeSubsequence(str1, str2)
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
