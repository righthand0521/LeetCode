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
    def removeDuplicates(self, s: str) -> str:
        retVal = ""

        stack = []
        for c in s:
            if not stack:
                stack.append(c)
                continue

            if stack[-1] == c:
                stack.pop()
            else:
                stack.append(c)
        retVal = "".join(stack)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["abbaca", "azxxzy", "bbaacaab", "xrjjjjjrp"]:
            # /* Example
            #  *  Input: s = "abbaca"
            #  *  Output: "ca"
            #  *
            #  *  Input: s = "azxxzy"
            #  *  Output: "ay"
            #  *
            #  *  Input: s = "bbaacaab"
            #  *  Output: "cb"
            #  *
            #  *  Input: s = "xrjjjjjrp"
            #  *  Output: "xrjrp"
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.removeDuplicates(s)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
