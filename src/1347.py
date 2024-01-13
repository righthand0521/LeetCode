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
    def minSteps(self, s: str, t: str) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        for cS, cT in zip(s, t):
            hashTable[cS] += 1
            hashTable[cT] -= 1

        for key in hashTable:
            if hashTable[key] > 0:
                retVal += hashTable[key]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print("")

        pSolution = Solution()
        for s, t in zip(["bab", "leetcode", "anagram"], ["aba", "practice", "mangaar"]):
            # /* Example
            #  *  Input: s = "bab", t = "aba"
            #  *  Output: 1
            #  *
            #  *  Input: s = "leetcode", t = "practice"
            #  *  Output: 5
            #  *
            #  *  Input: s = "anagram", t = "mangaar"
            #  *  Output: 0
            #  */
            logging.info("Input: s = \"%s\", t = \"%s\"", s, t)

            retVal = pSolution.minSteps(s, t)
            logging.info("Output: %s", retVal)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
