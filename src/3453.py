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
    def check(self, squares: List[List[int]], totalArea: int, limitY: int) -> bool:
        retVal = False

        area = 0
        for x, y, l in squares:
            if y < limitY:
                area += (l * min(limitY - y, l))
        retVal = area >= totalArea / 2

        return retVal

    def separateSquares(self, squares: List[List[int]]) -> float:
        retVal = 0

        maxY = 0
        totalArea = 0
        for x, y, l in squares:
            totalArea += (l**2)
            maxY = max(maxY, y + l)

        left = 0
        right = maxY
        eps = 1e-5
        while abs(right - left) > eps:
            middle = (right + left) / 2
            if self.check(squares, totalArea, middle):
                right = middle
            else:
                left = middle
        retVal = right

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for squares in [[[0, 0, 1], [2, 2, 1]], [[0, 0, 2], [1, 1, 1]]]:
            # /* Example
            #  *  Input: squares = [[0,0,1],[2,2,1]]
            #  *  Output: 1.00000
            #  *
            #  *  Input: squares = [[0,0,2],[1,1,1]]
            #  *  Output: 1.16667
            #  */
            logging.info("Input: squares = %s", squares)

            retVal = pSolution.separateSquares(squares)
            logging.info("Output: %.5f", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
