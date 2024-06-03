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
    def appendCharacters(self, s: str, t: str) -> int:
        retVal = 0

        sSize = len(s)
        tSize = len(t)

        idxS = 0
        idxT = 0
        while (idxS < sSize) and (idxT < tSize):
            if s[idxS] == t[idxT]:
                idxT += 1
            idxS += 1
        retVal = tSize - idxT

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, t in zip(["coaching", "abcde", "z"], ["coding", "a", "abcde"]):
            # /* Example
            #  *  Input: s = "coaching", t = "coding"
            #  *  Output: 4
            #  *
            #  *  Input: s = "abcde", t = "a"
            #  *  Output: 0
            #  *
            #  *  Input: s = "z", t = "abcde"
            #  *  Output: 5
            #  */
            logging.info("Input: s = \"%s\", t = \"%s\"", s, t)

            retVal = pSolution.appendCharacters(s, t)
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
