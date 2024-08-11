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
    def isValid(self, s: str) -> bool:
        retVal = False

        # s consists of parentheses only '()[]{}'.
        parenthesesMap = {
            '(': ')',
            '[': ']',
            '{': '}'
        }

        stack = []
        for pChar in s:
            if pChar in parenthesesMap:
                stack.append(parenthesesMap[pChar])
                continue

            if not stack:
                return retVal

            if stack.pop() != pChar:
                return retVal
        if not stack:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["()", "()[]{}", "(]"]:
            # /* Example
            #  *  Input: s = "()"
            #  *  Output: true
            #  *
            #  *  Input: s = "()[]{}"
            #  *  Output: true
            #  *
            #  *  Input: s = "(]"
            #  *  Output: false
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.isValid(s)
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
