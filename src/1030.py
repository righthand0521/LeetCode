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
    def allCellsDistOrder(self, rows: int, cols: int, rCenter: int, cCenter: int) -> List[List[int]]:
        retVal = []

        retVal = [(x, y) for x in range(rows) for y in range(cols)]
        retVal.sort(key=lambda x: abs(x[0] - rCenter) + abs(x[1] - cCenter))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rows, cols, rCenter, cCenter in zip([1, 2, 2], [2, 2, 3], [0, 0, 1], [0, 1, 2]):
            # /* Example
            # *  Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
            # *  Output: [[0, 0], [0, 1]]
            # *
            # *  Input: rows = 2, cols = 2, rCenter = 0, cCenter = 1
            # *  Output: [[0, 1], [0, 0], [1, 1], [1, 0]]
            # *
            # *  Input: rows = 2, cols = 3, rCenter = 1, cCenter = 2
            # *  Output: [[1, 2], [0, 2], [1, 1], [0, 1], [1, 0], [0, 0]]
            # */
            logging.info(
                "Input: rows = %s, cols = %s, rCenter = %s, cCenter = %s", rows, cols, rCenter, cCenter)

            retVal = pSolution.allCellsDistOrder(rows, cols, rCenter, cCenter)
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
