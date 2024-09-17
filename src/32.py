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
    def longestValidParentheses(self, s: str) -> int:
        retVal = 0

        stack = []
        stack.append(-1)

        for idx, value in enumerate(s):
            if value == '(':
                stack.append(idx)
                continue

            stack.pop()
            if not stack:
                stack.append(idx)
            else:
                retVal = max(retVal, idx-stack[-1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["(()", ")()())", ""]:
            # /* Example
            #  *  Input: s = "(()"
            #  *  Output: 2
            #  *
            #  *  Input: s = ")()())"
            #  *  Output: 4
            #  *
            #  *  Input: s = ""
            #  *  Output: 0
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.longestValidParentheses(s)
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
