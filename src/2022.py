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
    def construct2DArray(self, original: List[int], m: int, n: int) -> List[List[int]]:
        retVal = []

        originalSize = len(original)
        if originalSize != m * n:
            return retVal
        retVal = [[0] * n for _ in range(m)]

        originalIndex = 0
        for x in range(m):
            for y in range(n):
                retVal[x][y] = original[originalIndex]
                originalIndex += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, m, n in zip([[1, 2, 3, 4], [1, 2, 3], [1, 2]], [2, 1, 1], [2, 3, 1]):
            # /* Example
            #  *  Input: original = [1,2,3,4], m = 2, n = 2
            #  *  Output: [[1,2],[3,4]]
            #  *
            #  *  Input: original = [1,2,3], m = 1, n = 3
            #  *  Output: [[1,2,3]]
            #  *
            #  *  Input: original = [1,2], m = 1, n = 1
            #  *  Output: []
            #  */
            logging.info("Input: nums = %s, m = %s, n = %s", nums, m, n)

            retVal = pSolution.construct2DArray(nums, m, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
