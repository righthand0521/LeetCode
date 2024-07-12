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
    def maximumGain(self, s: str, x: int, y: int) -> int:
        retVal = 0

        # Ensure "ab" always has higher points than "ba"
        if x < y:
            s = s[::-1]
            x, y = y, x

        aCount = 0
        bCount = 0
        for c in s:
            if c == "a":
                aCount += 1
            elif c == "b":
                if aCount > 0:
                    aCount -= 1
                    retVal += x
                else:
                    bCount += 1
            else:
                retVal += min(bCount, aCount) * y
                aCount = 0
                bCount = 0
        retVal += min(bCount, aCount) * y

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, x, y in zip(["cdbcbbaaabab", "aabbaaxybbaabb"], [4, 5], [5, 4]):
            # /* Example
            #  *  Input: s = "cdbcbbaaabab", x = 4, y = 5
            #  *  Output: 19
            #  *
            #  *  Input: s = "aabbaaxybbaabb", x = 5, y = 4
            #  *  Output: 20
            #  */
            logging.info("Input: s = \"%s\", x = %s, y = %s", s, x, y)

            retVal = pSolution.maximumGain(s, x, y)
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
