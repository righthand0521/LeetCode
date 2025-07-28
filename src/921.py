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
    def minAddToMakeValid(self, s: str) -> int:
        retVal = 0

        openBrackets = 0
        minAddsRequired = 0
        for c in s:
            if c == '(':
                openBrackets += 1
            else:
                if openBrackets > 0:  # If open bracket exists, match it with the closing one.
                    openBrackets -= 1
                else:   # If not, we need to add a open bracket.
                    minAddsRequired += 1

        # Add the remaining open brackets as closing brackets would be required.
        retVal = minAddsRequired + openBrackets

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s in ["())", "((("]:
            # /* Example
            #  *  Input: s = "())"
            #  *  Output: 1
            #  *
            #  *  Input: s = "((("
            #  *  Output: 3
            #  */
            logging.info("Input: s = \"%s\"", s)

            retVal = pSolution.minAddToMakeValid(s)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
