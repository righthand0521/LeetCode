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
        self.letters = 26  # s consists only of lowercase English letters and '*'.

    def clearStars(self, s: str) -> str:
        retVal = ""

        lettersStack = [[] for _ in range(self.letters)]
        sArray = list(s)
        for i, c in enumerate(sArray):
            if c != "*":
                lettersStack[ord(c) - ord("a")].append(i)
                continue
            for j in range(self.letters):
                if lettersStack[j]:
                    sArray[lettersStack[j].pop()] = "*"
                    break
        retVal = "".join(c for c in sArray if c != "*")

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["aaba*", "abc"]:
            # /* Example
            #  *  Input: s = "aaba*"
            #  *  Output: "aab"
            #  *
            #  *  Input: s = "abc"
            #  *  Output: "abc"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.clearStars(s)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
