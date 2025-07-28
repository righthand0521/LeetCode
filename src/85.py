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
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        retVal = 0

        rowSize = len(matrix)
        if rowSize == 0:
            return retVal
        colSize = len(matrix[0])

        for i in range(rowSize):
            for j in range(colSize):
                if j == 0:
                    matrix[i][j] = int(matrix[i][j])
                else:
                    matrix[i][j] = matrix[i][j-1]+1 if matrix[i][j] == '1' else 0

        for j in range(colSize):
            monostack = list()
            left = [-1]*rowSize
            right = [rowSize]*rowSize
            for i in range(rowSize):
                while monostack and matrix[monostack[-1]][j] > matrix[i][j]:
                    right[monostack[-1]] = i
                    monostack.pop()
                left[i] = monostack[-1] if monostack else -1
                monostack.append(i)
            tmp = max((right[i]-left[i]-1)*matrix[i][j] for i in range(rowSize))
            retVal = max(retVal, tmp)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[["1", "0", "1", "0", "0"], ["1", "0", "1", "1", "1"], ["1", "1", "1", "1", "1"], ["1", "0", "0", "1", "0"]], [["0"]], [["1"]]]:
            # /* Example
            #  *  Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
            #  *  Output: 6
            #  *
            #  *  Input: matrix = [["0"]]
            #  *  Output: 0
            #  *
            #  *  Input: matrix = [["1"]]
            #  *  Output: 1
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.maximalRectangle(matrix)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
