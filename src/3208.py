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
    def numberOfAlternatingGroups(self, colors: List[int], k: int) -> int:
        retVal = 0

        colorsSize = len(colors)
        alternatingElementsCount = 1
        lastColor = colors[0]
        for i in range(1, colorsSize + k - 1):
            index = i % colorsSize

            # Check if current color is the same as the last color
            if colors[index] == lastColor:
                # Pattern breaks, reset sequence length
                alternatingElementsCount = 1
                lastColor = colors[index]
                continue

            # Extend sequence
            alternatingElementsCount += 1

            # If sequence length reaches at least k, count it
            if alternatingElementsCount >= k:
                retVal += 1

            lastColor = colors[index]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for colors, k in zip([[0, 1, 0, 1, 0], [0, 1, 0, 0, 1, 0, 1], [1, 1, 0, 1]], [3, 6, 4]):
            # /* Example
            #  *  Input: colors = [0,1,0,1,0], k = 3
            #  *  Output: 3
            #  *
            #  *  Input: colors = [0,1,0,0,1,0,1], k = 6
            #  *  Output: 2
            #  *
            #  *  Input: colors = [1,1,0,1], k = 4
            #  *  Output: 0
            #  */
            logging.info("Input: colors = %s, k = %s", colors, k)

            retVal = pSolution.numberOfAlternatingGroups(colors, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
