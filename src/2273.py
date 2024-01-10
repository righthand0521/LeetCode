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
    def removeAnagrams(self, words: List[str]) -> List[str]:
        retVal = []

        for s in words:
            if not retVal:
                retVal.append(s)
                compare = s
                continue

            if sorted(s) == sorted(compare):
                continue

            retVal.append(s)
            compare = s

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words in [["abba", "baba", "bbaa", "cd", "cd"],
                      ["a", "b", "c", "d", "e"],
                      ["z", "z", "z", "gsw", "wsg", "gsw", "krptu"]]:
            # /* Example
            #  *  Input: words = ["abba","baba","bbaa","cd","cd"]
            #  *  Output: ["abba","cd"]
            #  *
            #  *  Input: words = ["a","b","c","d","e"]
            #  *  Output: ["a","b","c","d","e"]
            #  *
            #  *  Input: words = ["z", "z", "z", "gsw", "wsg", "gsw", "krptu"]
            #  *  Output: ["z","gsw","krptu"]
            #  */
            logging.info("Input: words = %s", words)

            retVal = pSolution.removeAnagrams(words)
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
