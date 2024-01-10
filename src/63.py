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
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        retVal = 0

        if obstacleGrid[0][0] == 1:
            return retVal

        row = len(obstacleGrid)
        col = len(obstacleGrid[0])

        # /* Example
        #  *    | 0 1 2 | 0 1 2
        #  *  --+-------+-------
        #  *  0 | 0 0 0 | 1 1 1
        #  *  1 | 0 1 0 | 1 0 1
        #  *  2 | 0 0 0 | 1 1 2
        #  */
        obstacleGrid[0][0] = 1
        for i in range(1, row):
            obstacleGrid[i][0] = 1 if (
                (obstacleGrid[i-1][0] == 1) and (obstacleGrid[i][0] == 0)) else 0
        for i in range(1, col):
            obstacleGrid[0][i] = 1 if (
                (obstacleGrid[0][i-1] == 1) and (obstacleGrid[0][i] == 0)) else 0

        for i in range(1, row):
            for j in range(1, col):
                obstacleGrid[i][j] = (
                    obstacleGrid[i-1][j] + obstacleGrid[i][j-1]) if (obstacleGrid[i][j] == 0) else 0
        retVal = obstacleGrid[row-1][col-1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for obstacleGrid in [[[0, 0, 0], [0, 1, 0], [0, 0, 0]], [[0, 1], [0, 0]]]:
            # /* Example
            #  *  Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
            #  *  Output: 2
            #  *
            #  *  Input: obstacleGrid = [[0,1],[0,0]]
            #  *  Output: 1
            #  */
            logging.info("Input: obstacleGrid = %s", obstacleGrid)

            retVal = pSolution.uniquePathsWithObstacles(obstacleGrid)
            logging.info("Output: %d", retVal)

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
