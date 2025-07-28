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
    def canBeValid(self, s: str, locked: str) -> bool:
        retVal = False

        sSize = len(s)
        if sSize % 2 == 1:
            return retVal

        openBrackets = []
        unlocked = []
        for i in range(sSize):
            if locked[i] == "0":
                unlocked.append(i)
            elif s[i] == "(":
                openBrackets.append(i)
            elif s[i] == ")":
                if openBrackets:
                    openBrackets.pop()
                elif unlocked:
                    unlocked.pop()
                else:
                    return retVal

        while openBrackets and unlocked and openBrackets[-1] < unlocked[-1]:
            openBrackets.pop()
            unlocked.pop()
        if not openBrackets:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, locked in zip(["))()))", "()()", ")"], ["010100", "0000", "0"]):
            # /* Example
            #  *  Input: s = "))()))", locked = "010100"
            #  *  Output: true
            #  *
            #  *  Input: s = "()()", locked = "0000"
            #  *  Output: true
            #  *
            #  *  Input: s = ")", locked = "0"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\", locked = \"%s\"", s, locked)

            retVal = pSolution.canBeValid(s, locked)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
