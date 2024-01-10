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
    def isToeplitzMatrix(self, matrix: List[List[int]]) -> bool:
        for i in range(1, len(matrix)):
            for j in range(1, len(matrix[i])):
                if matrix[i-1][j-1] != matrix[i][j]:
                    return False

        return True


if __name__ == "__main__":
    logging_setting()

    logging.info("sys.version: %s", sys.version)
    print("")
    try:
        testCase = [
            [[1, 2, 3, 4], [5, 1, 2, 3], [9, 5, 1, 2]], [[1, 2], [2, 2]]
        ]

        pSolution = Solution()
        for i in range(0, len(testCase)):
            print("Input: matrix = [", end='')
            for j in range(0, len(testCase[i])):
                print('{comma}['.format(comma="" if j == 0 else ","), end="")
                for k in range(0, len(testCase[i][j])):
                    print('{comma}'.format(comma="" if k == 0 else ","), end="")
                    print(testCase[i][j][k], end="")
                print("]", end="")
            print("]")

            retVal = pSolution.isToeplitzMatrix(testCase[i])
            print("Output:", retVal)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
