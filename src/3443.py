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
    def maxDistance(self, s: str, k: int) -> int:
        retVal = 0

        latitude = 0
        longitude = 0
        sSize = len(s)
        for i in range(sSize):
            if s[i] == "N":
                latitude += 1
            elif s[i] == "S":
                latitude -= 1
            elif s[i] == "E":
                longitude += 1
            elif s[i] == "W":
                longitude -= 1
            retVal = max(retVal, min(abs(latitude) + abs(longitude) + k * 2, i + 1))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["NWSE", "NSWWEW"], [1, 3]):
            # /* Example
            #  *  Input: s = "NWSE", k = 1
            #  *  Output: 3
            #  *
            #  *  Input: s = "NSWWEW", k = 3
            #  *  Output: 6
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.maxDistance(s, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
