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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def getedges(self, fences: List[int], border: int) -> set:
        retVal = set()

        points = sorted([1] + fences + [border])
        pointsSize = len(points)
        for i in range(pointsSize - 1):
            for j in range(i + 1, pointsSize):
                retVal.add(points[j] - points[i])

        return retVal

    def maximizeSquareArea(self, m: int, n: int, hFences: List[int], vFences: List[int]) -> int:
        retVal = -1

        hEdges = self.getedges(hFences, m)
        vEdges = self.getedges(vFences, n)
        maxEdge = max(hEdges & vEdges, default=0)
        if maxEdge:
            retVal = (maxEdge * maxEdge) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for m, n,  hFences, vFences in [[4, 3, [2, 3], [2]], [6, 7, [2], [4]]]:
            # /* Example
            #  *  Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
            #  *  Output: 4
            #  *
            #  *  Input: m = 6, n = 7, hFences = [2], vFences = [4]
            #  *  Output: -1
            #  */
            logging.info("Input: m = %s, n = %s, hFences = %s, vFences = %s", m, n,  hFences, vFences)

            retVal = pSolution.maximizeSquareArea(m, n,  hFences, vFences)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
