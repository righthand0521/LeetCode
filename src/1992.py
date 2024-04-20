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
    def findFarmland(self, land: List[List[int]]) -> List[List[int]]:
        retVal = []

        landSize = len(land)
        landColSize = len(land[0])
        for row in range(landSize):
            for col in range(landColSize):
                if land[row][col] == 0:
                    continue

                x = row
                while x < landSize:
                    if land[x][col] == 0:
                        break
                    y = col
                    while y < landColSize:
                        if land[x][y] == 0:
                            break
                        land[x][y] = 0
                        y += 1
                    x += 1

                retVal.append([row, col, x-1, y-1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for land in [[[1, 0, 0], [0, 1, 1], [0, 1, 1]], [[1, 1], [1, 1]], [[0]], [[1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1]]]:
            # /* Example
            #  *  Input: land = [[1,0,0],[0,1,1],[0,1,1]]
            #  *  Output: [[0,0,0,0],[1,1,2,2]]
            #  *
            #  *  Input: land = [[1,1],[1,1]]
            #  *  Output: [[0,0,1,1]]
            #  *
            #  *  Input: land = [[0]]
            #  *  Output: []
            #  *
            #  *  Input: land = [[1,0,0,1,0,1,1,0,0,1,0,1,1]]
            #  *  Output: [[0,0,0,0],[0,3,0,3],[0,5,0,6],[0,9,0,9],[0,11,0,12]]
            #  */
            logging.info("Input: land = %s", land)

            retVal = pSolution.findFarmland(land)
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
