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
    def checkCuts(self, rectangles: list[list[int]], dim: int) -> bool:
        retVal = False

        # Sort rectangles by their starting coordinate in the given dimension
        rectangles.sort(key=lambda rect: rect[dim])

        furthestEnd = rectangles[0][dim + 2]  # Track the furthest ending coordinate seen so far
        gapCount = 0
        for i in range(1, len(rectangles)):
            rect = rectangles[i]
            # If current rectangle starts after the furthest end we've seen, we found a gap where a cut can be made
            if furthestEnd <= rect[dim]:
                gapCount += 1
            # Update the furthest ending coordinate
            furthestEnd = max(furthestEnd, rect[dim + 2])

        # We need at least 2 gaps to create 3 sections
        retVal = (gapCount >= 2)

        return retVal

    def checkValidCuts(self, n: int, rectangles: List[List[int]]) -> bool:
        retVal = False

        # Try both horizontal and vertical cuts
        retVal = self.checkCuts(rectangles, 0) or self.checkCuts(rectangles, 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, rectangles in zip([5, 4, 4],
                                 [[[1, 0, 5, 2], [0, 2, 2, 4], [3, 2, 5, 3], [0, 4, 4, 5]],
                                  [[0, 0, 1, 1], [2, 0, 3, 4], [0, 2, 2, 3], [3, 0, 4, 3]],
                                  [[0, 2, 2, 4], [1, 0, 3, 2], [2, 2, 3, 4], [3, 0, 4, 2], [3, 2, 4, 4]]]):
            # /* Example
            #  *  Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
            #  *  Output: true
            #  *
            #  *  Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]
            #  *  Output: true
            #  *
            #  *  Input: n = 4, rectangles = [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]
            #  *  Output: false
            #  */
            logging.info("Input: n = %s, rectangles = %s", n, rectangles)

            retVal = pSolution.checkValidCuts(n, rectangles)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
