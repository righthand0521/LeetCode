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
    def canChange(self, start: str, target: str) -> bool:
        retVal = True

        startSize = len(start)
        startIndex = 0
        targetIndex = 0
        while (startIndex < startSize) or (targetIndex < startSize):
            # skip underscores in start
            while (startIndex < startSize) and (start[startIndex] == "_"):
                startIndex += 1
            # skip underscores in target
            while (targetIndex < startSize) and (target[targetIndex] == "_"):
                targetIndex += 1

            # if one string exhausted, both strings should be exhausted
            if (startIndex == startSize) or (targetIndex == startSize):
                retVal = (startIndex == startSize) and (targetIndex == startSize)
                break

            # check if the pieces match and follow movement rules
            if start[startIndex] != target[targetIndex]:
                retVal = False
                break
            elif (start[startIndex] == "L") and (startIndex < targetIndex):
                retVal = False
                break
            elif (start[startIndex] == "R") and (startIndex > targetIndex):
                retVal = False
                break

            startIndex += 1
            targetIndex += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for start, target in zip(["_L__R__R_", "R_L_", "_R"], ["L______RR", "__LR", "R_"]):
            # /* Example
            #  *  Input: start = "_L__R__R_", target = "L______RR"
            #  *  Output: true
            #  *
            #  *  Input: start = "R_L_", target = "__LR"
            #  *  Output: false
            #  *
            #  *  Input: start = "_R", target = "R_"
            #  *  Output: false
            #  */
            logging.info("Input: start = \"%s\", target = \"%s\"", start, target)

            retVal = pSolution.canChange(start, target)
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
