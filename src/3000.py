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
    def areaOfMaxDiagonal(self, dimensions: List[List[int]]) -> int:
        retVal = 0

        maxDiagonal = 0
        for dimension in dimensions:
            width, height = dimension
            diagonal = (width ** 2 + height ** 2)
            area = width * height

            if diagonal > maxDiagonal:
                maxDiagonal = diagonal
                retVal = area
            elif diagonal == maxDiagonal:
                retVal = max(retVal, area)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for dimensions in [[[9, 3], [8, 6]], [[3, 4], [4, 3]]]:
            # /* Example
            #  *  Input: dimensions = [[9,3],[8,6]]
            #  *  Output: 48
            #  *
            #  *  Input: dimensions = [[3,4],[4,3]]
            #  *  Output: 12
            #  */
            logging.info("Input: dimensions = %s", dimensions)

            retVal = pSolution.areaOfMaxDiagonal(dimensions)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
