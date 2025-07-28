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
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        retVal = 0

        costSize = len(cost)
        dp = [0] * costSize
        dp[0] = cost[0]
        dp[1] = cost[1]
        for i in range(2, costSize):
            dp[i] = cost[i] + min(dp[i-1], dp[i-2])
        retVal = min(dp[costSize-1], dp[costSize-2])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for cost in [[10, 15, 20], [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]]:
            # /* Example
            #  *  Input: cost = [10,15,20]
            #  *  Output: 15
            #  *
            #  *  Input: cost = [1,100,1,1,1,100,1,1,100,1]
            #  *  Output: 6
            #  */
            logging.info("Input: cost = %s", cost)

            retVal = pSolution.minCostClimbingStairs(cost)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
