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
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        retVal = 0

        # Flatten the grid into numsArray
        numsArray = []
        for row in grid:
            for num in row:
                numsArray.append(num)
        numsArraySize = len(numsArray)

        # Sort numsArray in non-decreasing order to easily find the median
        numsArray.sort()

        # Store the median element as the final common value
        finalCommonNumber = numsArray[numsArraySize // 2]

        # Iterate through each number in numsArray
        for number in numsArray:
            # If the remainder when divided by x is different, return -1
            if number % x != finalCommonNumber % x:
                retVal = -1
                break
            # Add the number of operations required to make the current number equal to final_common_number
            retVal += abs(finalCommonNumber - number) // x

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid, x in [[[2, 4], [6, 8]], 2], [[[1, 5], [2, 3]], 1], [[[1, 2], [3, 4]], 2]:
            # /* Example
            #  *  Input: grid = [[2,4],[6,8]], x = 2
            #  *  Output: 4
            #  *
            #  *  Input: grid = [[1,5],[2,3]], x = 1
            #  *  Output: 5
            #  *
            #  *  Input: grid = [[1,2],[3,4]], x = 2
            #  *  Output: -1
            #  */
            logging.info("Input: grid = %s, x = %s", grid, x)

            retVal = pSolution.minOperations(grid, x)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
