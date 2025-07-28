import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def matrixScore(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        # Set score to summation of first column
        retVal = (1 << (gridColSize - 1)) * gridSize

        for col in range(1, gridColSize):
            count_same_bits = 0
            for row in range(gridSize):
                # Count elements matching first in row
                if grid[row][col] == grid[row][0]:
                    count_same_bits += 1

            # Calculate score based on the number of same bits in a column
            count_same_bits = max(count_same_bits, gridSize - count_same_bits)

            # Calculate the score contribution for the current column
            column_score = (1 << (gridColSize - col - 1)) * count_same_bits

            # Add contribution to score
            retVal += column_score

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 0, 1, 1], [1, 0, 1, 0], [1, 1, 0, 0]], [[0]]]:
            # /* Example
            #  *  Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
            #  *  Output: 39
            #  *
            #  *  Input: grid = [[0]]
            #  *  Output: 1
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.matrixScore(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
