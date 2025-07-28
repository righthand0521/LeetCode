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
    def luckyNumbers(self, matrix: List[List[int]]) -> List[int]:
        retVal = []

        for rowEntry in matrix:
            luckyIndex = 0
            luckyValue = rowEntry[luckyIndex]
            for key, value in enumerate(rowEntry):
                if value < luckyValue:
                    luckyIndex = key
                    luckyValue = value

            for rowEntry in matrix:
                value = rowEntry[luckyIndex]
                if value > luckyValue:
                    luckyIndex = -1
                    break

            if luckyIndex != -1:
                retVal.append(luckyValue)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for matrix in [[[3, 7, 8], [9, 11, 13], [15, 16, 17]],
                       [[1, 10, 4, 2], [9, 3, 8, 7], [15, 16, 17, 12]],
                       [[7, 8], [1, 2]]]:
            # /* Example
            #  *  Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
            #  *  Output: [15]
            #  *
            #  *  Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
            #  *  Output: [12]
            #  *
            #  *  Input: matrix = [[7,8],[1,2]]
            #  *  Output: [7]
            #  */
            logging.info("Input: matrix = %s", matrix)

            retVal = pSolution.luckyNumbers(matrix)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
