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
    def countAndSay(self, n: int) -> str:
        retVal = "1"

        for i in range(n-1):
            curr = ""
            pos = 0
            start = 0
            retValSize = len(retVal)
            while pos < retValSize:
                while (pos < retValSize) and (retVal[pos] == retVal[start]):
                    pos += 1
                curr += str(pos - start) + retVal[start]
                start = pos
            retVal = curr

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [4, 1]:
            # /* Example
            #  *  Input: n = 4
            #  *  Output: "1211"
            #  *
            #  *  Input: n = 1
            #  *  Output: "1"
            #  */
            logging.info("Input: n = %d", n)

            retVal = pSolution.countAndSay(n)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
