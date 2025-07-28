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
    def removeKdigits(self, num: str, k: int) -> str:
        retVal = ""

        numStack = []
        for digit in num:
            while k and numStack and numStack[-1] > digit:
                numStack.pop()
                k -= 1
            numStack.append(digit)

        if k > 0:
            numStack = numStack[:-k]

        retVal = "".join(numStack).lstrip('0') or "0"

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for num, k in zip(["1432219", "10200", "10"], [3, 1, 2]):
            # /* Example
            #  *  Input: num = "1432219", k = 3
            #  *  Output: "1219"
            #  *
            #  *  Input: num = "10200", k = 1
            #  *  Output: "200"
            #  *
            #  *  Input: num = "10", k = 2
            #  *  Output: "0"
            #  */
            logging.info("Input: num = \"%s\", k = %s", num, k)

            retVal = pSolution.removeKdigits(num, k)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
