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
    def gcdOfStrings(self, str1: str, str2: str) -> str:
        retVal = ""

        # /* Math: Greatest Common Divisor
        #  *  if str1 and str2 have Greatest Common Divisor of Strings
        #  *  let str1 = m * (substr), str2 = n * (substr)
        #  *  => str1 + str2 = m * (substr) + n * (substr) = (m + n)(substr)
        #  *  => str2 + str1 = n * (substr) + m * (substr) = (n + m)(substr)
        #  *  => str1 + str2 = str2 + str1
        #  *  let lenStr1 = m * lenSubstr, lenStr2 = n * lenSubstr
        #  *  => gcd(lenStr1, lenStr2) = lenSubstr
        #  *  Hence, str1 and str2 Greatest Common Divisor of Strings is str1[0:lenSubstr] or str2[0:lenSubstr]
        #  */
        if str1 + str2 != str2 + str1:
            return retVal

        gcdLength = gcd(len(str1), len(str2))
        retVal = str1[:gcdLength]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for str1, str2 in zip(["ABCABC", "ABABAB", "LEET", "TAUXXTAUXXTAUXXTAUXXTAUXX", "ABABCCABAB"],
                              ["ABC", "ABAB", "CODE", "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX", "ABAB"]):
            # /* Example
            #  *  Input: str1 = "ABCABC", str2 = "ABC"
            #  *  Output: "ABC"
            #  *
            #  *  Input: str1 = "ABABAB", str2 = "ABAB"
            #  *  Output: "AB"
            #  *
            #  *  Input: str1 = "LEET", str2 = "CODE"
            #  *  Output: ""
            #  *
            #  *  Input: str1 = "TAUXXTAUXXTAUXXTAUXXTAUXX", str2 = "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX"
            #  *  Output: "TAUXX"
            #  *
            #  *  Input: str1 = "ABABCCABAB", str2 = "ABAB"
            #  *  Output: ""
            #  */
            logging.info("Input: str1 = \"%s\", str2 = \"%s\"", str1, str2)

            retVal = pSolution.gcdOfStrings(str1, str2)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
