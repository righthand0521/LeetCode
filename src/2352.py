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
    def equalPairs(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        for row in range(gridSize):
            for col in range(gridSize):
                match = True

                for idx in range(gridSize):
                    if grid[row][idx] != grid[idx][col]:
                        match = False
                        break

                if match == True:
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[3, 2, 1], [1, 7, 6], [2, 7, 7]], [[3, 1, 2, 2], [1, 4, 4, 5], [2, 4, 2, 2], [2, 4, 2, 2]]]:
            # /* Example
            #  *  Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
            #  *  Output: 1
            #  *
            #  *  Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
            #  *  Output: 3
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.equalPairs(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
