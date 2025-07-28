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
    def maxEqualRowsAfterFlips(self, matrix: List[List[int]]) -> int:
        retVal = 0

        patternFrequency = {}  # Dictionary to store frequency of each pattern
        for currentRow in matrix:
            patternBuilder = ""

            # Convert row to pattern using list comprehension and
            # join 'T' if element matches first element, 'F' otherwise
            for cell in currentRow:
                if cell == currentRow[0]:
                    patternBuilder += "T"
                else:
                    patternBuilder += "F"

            # Update pattern frequency using dict.get() with default value
            patternFrequency[patternBuilder] = patternFrequency.get(patternBuilder, 0) + 1

        # Return maximum frequency using max() with default of 0
        retVal = max(patternFrequency.values(), default=0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[0, 1], [1, 1]], [[0, 1], [1, 0]], [[0, 0, 0], [0, 0, 1], [1, 1, 0]]]:
            # /* Example
            #  *  Input: matrix = [[0,1],[1,1]]
            #  *  Output: 1
            #  *
            #  *  Input: matrix = [[0,1],[1,0]]
            #  *  Output: 2
            #  *
            #  *  Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
            #  *  Output: 2
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.maxEqualRowsAfterFlips(matrix)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
