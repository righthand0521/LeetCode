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
    def __init__(self) -> None:
        self.method = 2

    def method_stack(self, s: str) -> str:
        retVal = ""

        stack = []
        for c in s:
            if c != '#':
                stack.append(c)
            elif stack:
                stack.pop()
        retVal = retVal.join(stack)

        return retVal

    def method_twoPointer(self, s: str, t: str) -> bool:
        retVal = False

        skipS = 0
        skipT = 0
        i = len(s) - 1
        j = len(t) - 1
        while i >= 0 or j >= 0:
            while i >= 0:
                if s[i] == "#":
                    skipS += 1
                    i -= 1
                elif skipS > 0:
                    skipS -= 1
                    i -= 1
                else:
                    break

            while j >= 0:
                if t[j] == "#":
                    skipT += 1
                    j -= 1
                elif skipT > 0:
                    skipT -= 1
                    j -= 1
                else:
                    break

            if i >= 0 and j >= 0:
                if s[i] != t[j]:
                    return retVal
            elif i >= 0 or j >= 0:
                return retVal

            i -= 1
            j -= 1

        retVal = True

        return retVal

    def backspaceCompare(self, s: str, t: str) -> bool:
        retVal = False

        if self.method == 1:
            if self.method_stack(s) == self.method_stack(t):
                retVal = True
        elif self.method == 2:
            retVal = self.method_twoPointer(s, t)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, t in zip(["ab#c", "ab##", "a#c", "a##c"], ["ad#c", "c#d#", "b", "#a#c"]):
            # /* Example
            #  *  Input: s = "ab#c", t = "ad#c"
            #  *  Output: true
            #  *
            #  *  Input: s = "ab##", t = "c#d#"
            #  *  Output: true
            #  *
            #  *  Input: s = "a#c", t = "b"
            #  *  Output: false
            #  *
            #  *  Input: s = "a##c", t = "#a#c"
            #  *  Output: true
            #  */
            logging.info("Input: s = \"%s\", t = \"%s\"", s, t)

            retVal = pSolution.backspaceCompare(s, t)
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
