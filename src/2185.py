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
    def prefixCount(self, words: List[str], pref: str) -> int:
        retVal = 0

        for word in words:
            if word.startswith(pref):
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, pref in zip(
                [["pay", "attention", "practice", "attend"], ["leetcode", "win", "loops", "success"]], ["at", "code"]):
            # /* Example
            #  *  Input: words = ["pay","attention","practice","attend"], pref = "at"
            #  *  Output: 2
            #  *
            #  *  Input: words = ["leetcode","win","loops","success"], pref = "code"
            #  *  Output: 0
            #  */
            logging.info("Input: words = %s, pref = %s", words, pref)

            retVal = pSolution.prefixCount(words, pref)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
