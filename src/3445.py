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
    def getStatus(self, a: int, b: int) -> int:
        retVal = ((a & 1) << 1) | (b & 1)

        return retVal

    def maxDifference(self, s: str, k: int) -> int:
        retVal = float("-inf")

        sSize = len(s)
        for a in ["0", "1", "2", "3", "4"]:  # s consists only of digits '0' to '4'.
            for b in ["0", "1", "2", "3", "4"]:  # s consists only of digits '0' to '4'.
                if a == b:
                    continue

                best = [float("inf")] * 4
                aCurrent = 0
                bCurrent = 0
                aPrevious = 0
                bPrevious = 0
                left = -1
                for right in range(sSize):
                    aCurrent += (s[right] == a)
                    bCurrent += (s[right] == b)
                    while (right - left >= k) and (bCurrent - bPrevious >= 2):
                        leftStatus = self.getStatus(aPrevious, bPrevious)
                        best[leftStatus] = min(best[leftStatus], aPrevious - bPrevious)
                        left += 1
                        aPrevious += s[left] == a
                        bPrevious += s[left] == b

                    rightStatus = self.getStatus(aCurrent, bCurrent)
                    if best[rightStatus ^ 0b10] != float("inf"):
                        retVal = max(retVal, aCurrent - bCurrent - best[rightStatus ^ 0b10])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, k in zip(["12233", "1122211", "110"], [4, 3, 3]):
            # /* Example
            #  *  Input: s = "12233", k = 4
            #  *  Output: -1
            #  *
            #  *  Input: s = "1122211", k = 3
            #  *  Output: 1
            #  *
            #  *  Input: s = "110", k = 3
            #  *  Output: -1
            #  */
            logging.info("Input: s = \"%s\", k = %s", s, k)

            retVal = pSolution.maxDifference(s, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
