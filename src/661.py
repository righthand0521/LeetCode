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
    def imageSmoother(self, img: List[List[int]]) -> List[List[int]]:
        retVal = []

        rowSize = len(img)
        colSize = len(img[0])

        retVal = [[0] * colSize for _ in range(rowSize)]
        for i in range(rowSize):
            for j in range(colSize):
                sum = 0
                count = 0
                for x in (i - 1, i, i + 1):
                    for y in (j - 1, j, j + 1):
                        if (0 <= x < rowSize) and (0 <= y < colSize):
                            sum += img[x][y]
                            count += 1
                retVal[i][j] = sum // count

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for img in [[[1, 1, 1], [1, 0, 1], [1, 1, 1]], [[100, 200, 100], [200, 50, 200], [100, 200, 100]]]:
            # /* Example
            #  *  Input: img = [[1,1,1],[1,0,1],[1,1,1]]
            #  *  Output: [[0,0,0],[0,0,0],[0,0,0]]
            #  *
            #  *  Input: img = [[100,200,100],[200,50,200],[100,200,100]]
            #  *  Output: [[137,141,137],[141,138,141],[137,141,137]]
            #  */
            logging.info("Input: img = %s", img)

            retVal = pSolution.imageSmoother(img)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
