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
    def champagneTower(self, poured: int, query_row: int, query_glass: int) -> float:
        retVal = 0

        glass = [poured]
        for row in range(query_row):
            glassSize = len(glass)
            nextGlass = [0] * (glassSize + 1)
            for col in range(glassSize):
                volume = glass[col]
                if volume <= 1:
                    continue
                nextGlass[col] += (volume - 1) / 2
                nextGlass[col + 1] += (volume - 1) / 2
            glass = nextGlass
        retVal = min(1, glass[query_glass])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for poured, query_row, query_glass in zip([1, 2, 100000009], [1, 1, 33], [1, 1, 17]):
            # /* Example
            #  *  Input: poured = 1, query_row = 1, query_glass = 1
            #  *  Output: 0.00000
            #  *
            #  *  Input: poured = 2, query_row = 1, query_glass = 1
            #  *  Output: 0.50000
            #  *
            #  *  Input: poured = 100000009, query_row = 33, query_glass = 17
            #  *  Output: 1.00000
            #  */
            logging.info("Input: poured = %s, query_row = %s, query_glass = %s",
                         poured, query_row, query_glass)

            retVal = pSolution.champagneTower(poured, query_row, query_glass)
            logging.info("Output: %.5f", retVal)

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
