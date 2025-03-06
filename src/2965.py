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
    def findMissingAndRepeatedValues(self, grid: List[List[int]]) -> List[int]:
        retVal = []

        # Store frequency of each number in the grid
        freq = {}
        for row in grid:
            for num in row:
                freq[num] = freq.get(num, 0) + 1

        # Check numbers from 1 to n^2 to find missing and repeated values
        gridSize = len(grid)
        for num in range(1, gridSize * gridSize + 1):
            if num not in freq:
                missing = num
            elif freq[num] == 2:
                repeat = num
        retVal = [repeat, missing]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 3], [2, 2]], [[9, 1, 7], [8, 9, 2], [3, 4, 6]]]:
            # /* Example
            #  *  Input: grid = [[1,3],[2,2]]
            #  *  Output: [2,4]
            #  *
            #  *  Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
            #  *  Output: [9,5]
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.findMissingAndRepeatedValues(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
