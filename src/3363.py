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
    def dp(self, fruits: List[List[int]]) -> int:
        retVal = 0

        fruitsSize = len(fruits)
        prev = [float("-inf")] * fruitsSize
        curr = [float("-inf")] * fruitsSize

        prev[fruitsSize - 1] = fruits[0][fruitsSize - 1]
        for i in range(1, fruitsSize - 1):
            for j in range(max(fruitsSize - 1 - i, i + 1), fruitsSize):
                best = prev[j]
                if j - 1 >= 0:
                    best = max(best, prev[j - 1])
                if j + 1 < fruitsSize:
                    best = max(best, prev[j + 1])
                curr[j] = best + fruits[i][j]
            prev, curr = curr, prev
        retVal = prev[fruitsSize - 1]

        return retVal

    def maxCollectedFruits(self, fruits: List[List[int]]) -> int:
        retVal = 0

        fruitsSize = len(fruits)

        retVal = sum(fruits[i][i] for i in range(fruitsSize))
        retVal += self.dp(fruits)
        for i in range(fruitsSize):
            for j in range(i):
                fruits[i][j], fruits[j][i] = fruits[j][i], fruits[i][j]
        retVal += self.dp(fruits)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for fruits in [[[1, 2, 3, 4], [5, 6, 8, 7], [9, 10, 11, 12], [13, 14, 15, 16]], [[1, 1], [1, 1]]]:
            # /* Example
            #  *  Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
            #  *  Output: 100
            #  *
            #  *  Input: fruits = [[1,1],[1,1]]
            #  *  Output: 4
            #  */
            logging.info("Input: fruits = %s", fruits)

            retVal = pSolution.maxCollectedFruits(fruits)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
