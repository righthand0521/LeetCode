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
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        retVal = 0

        triangleSize = len(triangle)
        dp = [[0] * triangleSize for _ in range(triangleSize)]
        dp[0][0] = triangle[0][0]

        for i in range(1, triangleSize):
            dp[i][0] = dp[i - 1][0] + triangle[i][0]
            for j in range(1, i):
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j]
            dp[i][i] = dp[i - 1][i - 1] + triangle[i][i]

        retVal = dp[triangleSize - 1][0]
        for i in range(1, triangleSize):
            retVal = min(retVal, dp[triangleSize - 1][i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for triangle in [[[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]], [[-10]]]:
            # /* Example
            #  *  Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
            #  *  Output: 11
            #  *
            #  *  Input: triangle = [[-10]]
            #  *  Output: -10
            #  */
            logging.info("Input: triangle = %s", triangle)

            retVal = pSolution.minimumTotal(triangle)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
