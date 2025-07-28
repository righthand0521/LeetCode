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
    def isMagicSquare(self, grid: List[List[int]], row: int, col: int) -> int:
        retVal = 0

        # while a magic square can only contain numbers from 1 to 9
        seen = [0] * 10
        for x in range(3):
            for y in range(3):
                num = grid[row+x][col+y]
                if (num < 1) or (num > 9):
                    return retVal
                elif seen[num]:
                    return retVal

                seen[num] = 1

        diagonal1 = grid[row][col] + grid[row+1][col+1] + grid[row+2][col+2]
        diagonal2 = grid[row+2][col] + grid[row+1][col+1] + grid[row][col+2]
        if diagonal1 != diagonal2:
            return retVal

        row1 = grid[row][col] + grid[row][col+1] + grid[row][col+2]
        row2 = grid[row+1][col] + grid[row+1][col+1] + grid[row+1][col+2]
        row3 = grid[row+2][col] + grid[row+2][col+1] + grid[row+2][col+2]
        if (row1 != diagonal1) or (row2 != diagonal1) or (row3 != diagonal1):
            return retVal

        col1 = grid[row][col] + grid[row+1][col] + grid[row+2][col]
        col2 = grid[row][col+1] + grid[row+1][col+1] + grid[row+2][col+1]
        col3 = grid[row][col+2] + grid[row+1][col+2] + grid[row+2][col+2]
        if (col1 != diagonal1) or (col2 != diagonal1) or (col3 != diagonal1):
            return retVal

        retVal = 1

        return retVal

    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])  # 1 <= row, col <= 10
        if (rowSize < 3) or (colSize < 3):
            return retVal

        for x in range(rowSize-2):
            for y in range(colSize-2):
                retVal += self.isMagicSquare(grid, x, y)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[4, 3, 8, 4], [9, 5, 1, 9], [2, 7, 6, 2]], [[8]]]:
            # /* Example
            #  *  Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
            #  *  Output: 1
            #  *
            #  *  Input: grid = [[8]]
            #  *  Output: 0
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.numMagicSquaresInside(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
