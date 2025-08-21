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
    def numSubmat(self, mat: List[List[int]]) -> int:
        retVal = 0

        matColSize = len(mat[0])
        heights = [0] * matColSize

        for row in mat:
            for i, x in enumerate(row):
                heights[i] = 0 if x == 0 else heights[i] + 1

            monotonicStack = [[-1, 0, -1]]
            for i, h in enumerate(heights):
                while monotonicStack[-1][2] >= h:
                    monotonicStack.pop()

                j, prev, _ = monotonicStack[-1]
                cur = prev + (i - j) * h
                monotonicStack.append([i, cur, h])

                retVal += cur

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for mat in [[[1, 0, 1], [1, 1, 0], [1, 1, 0]], [[0, 1, 1, 0], [0, 1, 1, 1], [1, 1, 1, 0]]]:
            # /* Example
            #  *  Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
            #  *  Output: 13
            #  *
            #  *  Input: mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
            #  *  Output: 24
            #  */
            logging.info("Input: mat = %s", mat)

            retVal = pSolution.numSubmat(mat)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
