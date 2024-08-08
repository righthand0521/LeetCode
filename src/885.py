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
    def spiralMatrixIII(self, rows: int, cols: int, rStart: int, cStart: int) -> List[List[int]]:
        retVal = []

        # East, South, West, North
        directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]

        step = 1
        idx = 0
        retValSize = len(retVal)
        while retValSize < (rows * cols):
            for _ in range(2):
                for _ in range(step):
                    if ((rStart >= 0) and (rStart < rows) and (cStart >= 0) and (cStart < cols)):
                        retVal.append([rStart, cStart])
                    rStart += directions[idx][0]
                    cStart += directions[idx][1]
                idx = (idx + 1) % 4
            step += 1
            retValSize = len(retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rows, cols, rStart, cStart in zip([1, 5], [4, 6], [0, 1], [0, 4]):
            # /* Example
            #  *  Input: rows = 1, cols = 4, rStart = 0, cStart = 0
            #  *  Output: [[0,0],[0,1],[0,2],[0,3]]
            #  *
            #  *  Input: rows = 5, cols = 6, rStart = 1, cStart = 4
            #  *  Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],
            #  *  [4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
            #  */
            logging.info("Input: rows = %s, cols = %s, rStart = %s, cStart = %s", rows, cols, rStart, cStart)

            retVal = pSolution.spiralMatrixIII(rows, cols, rStart, cStart)
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
