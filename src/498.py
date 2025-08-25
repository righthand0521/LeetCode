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
        datefmt='%Y/%m/%d %H:%matColSize:%S')


class Solution:
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        retVal = []

        if not mat or not mat[0]:
            return retVal

        matSize = len(mat)
        matColSize = len(mat[0])
        row = 0
        column = 0
        direction = 1
        while (row < matSize) and (column < matColSize):
            retVal.append(mat[row][column])

            # Move along in the current diagonal depending upon the current direction.[i, j] -> [i - 1, j + 1]
            # if going up and [i, j] -> [i + 1][j - 1] if going down.
            nextRow = row + (-1 if direction == 1 else 1)
            nextColumn = column + (1 if direction == 1 else -1)

            # Checking if the next element in the diagonal is within the bounds of the mat or not.
            # If it's not within the bounds, we have to find the next head.
            if (nextRow < 0) or (nextRow == matSize) or (nextColumn < 0) or (nextColumn == matColSize):
                # If the current diagonal was going in the upwards direction.
                if direction:
                    # For an upwards going diagonal having [i, j] as its tail
                    # If [i, j + 1] is within bounds, then it becomes the next head. Otherwise, the element directly below
                    # i.e. the element [i + 1, j] becomes the next head
                    row += (column == matColSize - 1)
                    column += (column < matColSize - 1)
                else:
                    # For a downwards going diagonal having [i, j] as its tail
                    # if [i + 1, j] is within bounds, then it becomes the next head. Otherwise, the element directly below
                    # i.e. the element [i, j + 1] becomes the next head
                    column += (row == matSize - 1)
                    row += (row < matSize - 1)

                # Flip the direction
                direction = 1 - direction
            else:
                row = nextRow
                column = nextColumn

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mat in [[[1, 2, 3], [4, 5, 6], [7, 8, 9]], [[1, 2], [3, 4]]]:
            # /* Example
            #  *  Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
            #  *  Output: [1,2,4,7,5,3,6,8,9]
            #  *
            #  *  Input: mat = [[1,2],[3,4]]
            #  *  Output: [1,2,3,4]
            #  */
            logging.info("Input: mat = %s", mat)

            retVal = pSolution.findDiagonalOrder(mat)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
