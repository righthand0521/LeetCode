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
    def areAlmostEqual(self, s1: str, s2: str) -> bool:
        retVal = False

        s1Size = len(s1)
        firstIndexDiff = 0
        secondIndexDiff = 0
        numDiffs = 0
        for i in range(s1Size):
            if s1[i] == s2[i]:
                continue

            numDiffs += 1
            if numDiffs > 2:  # numDiffs is more than 2, one string swap will not make two strings equal
                return retVal
            elif numDiffs == 1:
                firstIndexDiff = i  # store the index of first difference
            else:
                secondIndexDiff = i  # store the index of second difference

        # check if swap is possible
        retVal = (s1[firstIndexDiff] == s2[secondIndexDiff]) and (s1[secondIndexDiff] == s2[firstIndexDiff])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s1, s2 in zip(["bank", "attack", "kelb"], ["kanb", "defend", "kelb"]):
            # /* Example
            #  *  Input: s1 = "bank", s2 = "kanb"
            #  *  Output: true
            #  *
            #  *  Input: s1 = "attack", s2 = "defend"
            #  *  Output: false
            #  *
            #  *  Input: s1 = "kelb", s2 = "kelb"
            #  *  Output: true
            #  */
            logging.info("Input: s1 = \"%s\", s2 = \"%s\"", s1, s2)

            retVal = pSolution.areAlmostEqual(s1, s2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
