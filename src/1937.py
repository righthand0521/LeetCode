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
    def maxPoints(self, points: List[List[int]]) -> int:
        retVal = 0

        row = len(points)
        col = len(points[0])    # 1 <= m, n <= 10^5
        dp = [[0 for j in range(col)] for _ in range(row)]
        dp[0] = points[0]

        # https://leetcode.com/problems/maximum-number-of-points-with-cost/solutions/1344888/c-dp-from-o-m-n-n-to-o-m-n/
        #   dp[i][j] = max(dp[i - 1][k] + point[i][j] - abs(j - k)) for each 0 <= k < points[i - 1].size()
        #   => dp[i][j] = max(dp[i - 1][k] + k) + points[i][j] - j for all 0 <= k <= j
        #   => dp[i][j] = max(dp[i - 1][k] - k) + points[i][j] + j for all j <= k <= points[i].size() - 1
        for i in range(1, row):
            dpLeft = [0 for j in range(col)]
            dpLeft[0] = dp[i - 1][0]
            for k in range(1, col):
                dpLeft[k] = max(dpLeft[k-1], dp[i-1][k]+k)

            dpRight = [0 for j in range(col)]
            dpRight[col-1] = dp[i - 1][col-1] - col + 1
            for k in range(col-2, -1, -1):
                dpRight[k] = max(dpRight[k+1], dp[i-1][k]-k)

            for j in range(col):
                dp[i][j] = max(dpLeft[j] - j, dpRight[j] + j) + points[i][j]

        retVal = max(dp[row-1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[1, 2, 3], [1, 5, 1], [3, 1, 1]], [[1, 5], [2, 3], [4, 2]]]:
            # /* Example
            #  *  Input: points = [[1,2,3],[1,5,1],[3,1,1]]
            #  *  Output: 9
            #  *
            #  *  Input: points = [[1,5],[2,3],[4,2]]
            #  *  Output: 11
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.maxPoints(points)
            logging.info("Output: %d", retVal)

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
