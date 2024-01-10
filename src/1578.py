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
    def minCost(self, colors: str, neededTime: List[int]) -> int:
        retVal = 0

        colorsSize = len(colors)

        i = 0
        while i < colorsSize:
            previous = colors[i]
            maxNeededTime = 0
            cost = 0
            while i < colorsSize and colors[i] == previous:
                maxNeededTime = max(maxNeededTime, neededTime[i])
                cost += neededTime[i]
                i += 1
            retVal += cost - maxNeededTime

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for colors, neededTime in zip(["abaac", "abc", "aabaa"], [[1, 2, 3, 4, 5], [1, 2, 3], [1, 2, 3, 4, 1]]):
            # /* Example
            #  *  Input: colors = "abaac", neededTime = [1,2,3,4,5]
            #  *  Output: 3
            #  *
            #  *  Input: colors = "abc", neededTime = [1,2,3]
            #  *  Output: 0
            #  *
            #  *  Input: colors = "aabaa", neededTime = [1,2,3,4,1]
            #  *  Output: 2
            #  */
            logging.info("Input: colors = \"%s\", neededTime = %s",
                         colors, neededTime)

            retVal = pSolution.minCost(colors, neededTime)
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
