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
    def longestDiverseString(self, a: int, b: int, c: int) -> str:
        retVal = ""

        curra = 0
        currb = 0
        currc = 0
        totalIterations = a + b + c
        for _ in range(totalIterations):
            if (a >= b and a >= c and curra != 2):
                retVal += "a"
                a -= 1
                curra += 1
                currb = 0
                currc = 0
            elif (a > 0 and (currb == 2 or currc == 2)):
                retVal += "a"
                a -= 1
                curra += 1
                currb = 0
                currc = 0
            elif (b >= a and b >= c and currb != 2):
                retVal += "b"
                b -= 1
                currb += 1
                curra = 0
                currc = 0
            elif (b > 0 and (currc == 2 or curra == 2)):
                retVal += "b"
                b -= 1
                currb += 1
                curra = 0
                currc = 0
            elif (c >= a and c >= b and currc != 2):
                retVal += "c"
                c -= 1
                currc += 1
                curra = 0
                currb = 0
            elif (c > 0 and (curra == 2 or currb == 2)):
                retVal += "c"
                c -= 1
                currc += 1
                curra = 0
                currb = 0

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for a, b, c in zip([1, 7], [1, 1], [7, 0]):
            # /* Example
            #  *  Input: a = 1, b = 1, c = 7
            #  *  Output: "ccaccbcc"
            #  *
            #  *  Input: a = 7, b = 1, c = 0
            #  *  Output: "aabaa"
            #  */
            logging.info("Input: a = %s, b = %s, c = %s", a, b, c)

            retVal = pSolution.longestDiverseString(a, b, c)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
