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
    def parseBoolExpr(self, expression: str) -> bool:
        retVal = False

        stack = deque()
        for c in expression:
            if c == "," or c == "(":
                continue
            elif c in ["t", "f", "!", "&", "|"]:
                stack.append(c)
            elif c == ")":
                hasTrue = False
                hasFalse = False
                while stack[-1] not in ["!", "&", "|"]:
                    topValue = stack.pop()
                    if topValue == "t":
                        hasTrue = True
                    elif topValue == "f":
                        hasFalse = True

                op = stack.pop()
                if op == "!":
                    stack.append("f" if (hasTrue == True) else "t")
                elif op == "&":
                    stack.append("f" if (hasFalse == True) else "t")
                else:
                    stack.append("t" if (hasTrue == True) else "f")

        if stack[-1] == "t":
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for expression in ["&(|(f))", "|(f,f,f,t)", "!(&(f,t))"]:
            # /* Example
            #  *  Input: expression = "&(|(f))"
            #  *  Output: false
            #  *
            #  *  Input: expression = "|(f,f,f,t)"
            #  *  Output: true
            #  *
            #  *  Input: expression = "!(&(f,t))"
            #  *  Output: true
            #  */
            logging.info("Input: s = \"%s\"", expression)

            retVal = pSolution.parseBoolExpr(expression)
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
