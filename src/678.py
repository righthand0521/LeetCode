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
    def checkValidString(self, s: str) -> bool:
        retVal = False

        sSize = len(s)

        leftParenthesis = 0
        rightParenthesis = 0
        for left in range(sSize):
            if (s[left] == '(') or (s[left] == '*'):
                leftParenthesis += 1
            elif s[left] == ')':
                leftParenthesis -= 1

            right = sSize - 1 - left
            if (s[right] == ')') or (s[right] == '*'):
                rightParenthesis += 1
            elif s[right] == '(':
                rightParenthesis -= 1

            if (leftParenthesis < 0) or (rightParenthesis < 0):
                return retVal

        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["()", "(*)", "(*))"]:
            # /* Example
            #  *  Input: s = "()"
            #  *  Output: true
            #  *
            #  *  Input: s = "(*)"
            #  *  Output: true
            #  *
            #  *  Input: s = "(*))"
            #  *  Output: true
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.checkValidString(s)
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
