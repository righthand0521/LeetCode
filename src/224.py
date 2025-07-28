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
    def calculate(self, s: str) -> int:
        retVal = 0

        stack = []
        sign = 1
        num = 0
        for c in s:
            if c.isdigit():
                num = num * 10 + int(c)
            elif (c == '+') or (c == '-'):
                retVal += (sign * num)
                num = 0
                sign = -1
                if c == '+':
                    sign = 1
            elif (c == '('):
                stack.append(retVal)
                stack.append(sign)
                retVal = 0
                sign = 1
            elif (c == ')'):
                retVal += (sign * num)
                num = 0
                retVal *= stack[-1]
                stack.pop()
                retVal += stack[-1]
                stack.pop()
        retVal += (sign * num)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["1 + 1", " 2-1 + 2 ", "(1+(4+5+2)-3)+(6+8)", "1-(     -2)"]:
            # /* Example
            #  *  Input: s = "1 + 1"
            #  *  Output: 2
            #  *
            #  *  Input: s = " 2-1 + 2 "
            #  *  Output: 3
            #  *
            #  *  Input: s = "(1+(4+5+2)-3)+(6+8)"
            #  *  Output: 23
            #  *
            #  *  Input: s = "1-(     -2)"
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.calculate(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
