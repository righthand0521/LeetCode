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
    def checkMatch(self, stack: list, part: str, partLength: int) -> bool:
        retVal = False

        if "".join(stack[-partLength:]) == part:
            retVal = True

        return retVal

    def removeOccurrences(self, s: str, part: str) -> str:
        retVal = ""

        partSize = len(part)
        stack = []
        for char in s:
            stack.append(char)
            stackSize = len(stack)
            if (stackSize < partSize) or (self.checkMatch(stack, part, partSize) == False):
                continue
            for _ in range(partSize):
                stack.pop()
        retVal = "".join(stack)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, part in zip(["daabcbaabcbc", "axxxxyyyyb"], ["abc", "xy"]):
            # /* Example
            #  *  Input: s = "daabcbaabcbc", part = "abc"
            #  *  Output: "dab"
            #  *
            #  *  Input: s = "axxxxyyyyb", part = "xy"
            #  *  Output: "ab"
            #  */
            logging.info("Input: s = \"%s\", part = \"%s\"", s, part)

            retVal = pSolution.removeOccurrences(s, part)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
