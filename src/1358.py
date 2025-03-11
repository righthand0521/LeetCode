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
    def numberOfSubstrings(self, s: str) -> int:
        retVal = 0

        lastPos = [-1] * 3  # Track last position of a, b, c
        sSize = len(s)
        for pos in range(sSize):
            # Update last position of current character
            lastPos[ord(s[pos]) - ord("a")] = pos

            # Add count of valid substrings ending at current position
            # If any character is missing, min will be -1
            # Else min gives leftmost required character position
            retVal += 1 + min(lastPos)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abcabc", "aaacb", "abc"]:
            # /* Example
            #  *  Input: s = "abcabc"
            #  *  Output: 10
            #  *
            #  *  Input: s = "aaacb"
            #  *  Output: 3
            #  *
            #  *  Input: s = "abc"
            #  *  Output: 1
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.numberOfSubstrings(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
