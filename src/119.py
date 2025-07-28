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
    def getRow(self, rowIndex: int) -> List[int]:
        retVal = [1] * (rowIndex + 1)

        for row in range(rowIndex):
            for col in range(row, 0, -1):
                retVal[col] += retVal[col - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rowIndex in [3, 0, 1]:
            # /* Example
            #  *  Input: rowIndex = 3
            #  *  Output: [1,3,3,1]
            #  *
            #  *  Input: rowIndex = 0
            #  *  Output: [1]
            #  *
            #  *  Input: rowIndex = 1
            #  *  Output: [1,1]
            #  */
            logging.info("Input: rowIndex = %s", rowIndex)

            retVal = pSolution.getRow(rowIndex)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
