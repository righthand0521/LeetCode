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
    def dfs(self, g: List[List[int]], u: int, present: List[int], future: List[int], budget: int) -> tuple:
        cost = present[u]
        dCost = present[u] // 2

        # dp[u][state][budget]
        # state = 0: Do not purchase parent node, state = 1: Must purchase parent node
        dp0 = [0] * (budget + 1)
        dp1 = [0] * (budget + 1)

        # subProfit[state][budget]
        # state = 0: discount not available, state = 1: discount available
        subProfit0 = [0] * (budget + 1)
        subProfit1 = [0] * (budget + 1)
        uSize = cost

        for v in g[u]:
            child_dp0, child_dp1, vSize = self.dfs(g, v, present, future, budget)
            uSize += vSize
            for i in range(budget, -1, -1):
                for sub in range(min(vSize, i) + 1):
                    if i - sub >= 0:
                        subProfit0[i] = max(subProfit0[i], subProfit0[i - sub] + child_dp0[sub],)
                        subProfit1[i] = max(subProfit1[i], subProfit1[i - sub] + child_dp1[sub],)

        for i in range(budget + 1):
            dp0[i] = subProfit0[i]
            dp1[i] = subProfit0[i]
            if i >= dCost:
                dp1[i] = max(subProfit0[i], subProfit1[i - dCost] + future[u] - dCost)
            if i >= cost:
                dp0[i] = max(subProfit0[i], subProfit1[i - cost] + future[u] - cost)

        return dp0, dp1, uSize

    def maxProfit(self, n: int, present: List[int], future: List[int], hierarchy: List[List[int]], budget: int) -> int:
        retVal = 0

        g = [[] for _ in range(n)]
        for e in hierarchy:
            g[e[0] - 1].append(e[1] - 1)
        retVal = self.dfs(g, 0, present, future, budget)[0][budget]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, present, future, hierarchy, budget in [[2, [1, 2], [4, 3], [[1, 2]], 3],
                                                      [2, [3, 4], [5, 8], [[1, 2]], 4],
                                                      [3, [4, 6, 8], [7, 9, 11], [[1, 2], [1, 3]], 10],
                                                      [3, [5, 2, 3], [8, 5, 6], [[1, 2], [2, 3]], 7]]:
            # /* Example
            #  *  Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3
            #  *  Output: 5
            #  *
            #  *  Input: n = 2, present = [3,4], future = [5,8], hierarchy = [[1,2]], budget = 4
            #  *  Output: 4
            #  *
            #  *  Input: n = 3, present = [4,6,8], future = [7,9,11], hierarchy = [[1,2],[1,3]], budget = 10
            #  *  Output: 10
            #  *
            #  *  Input: n = 3, present = [5,2,3], future = [8,5,6], hierarchy = [[1,2],[2,3]], budget = 7
            #  *  Output: 12
            #  */
            logging.info("Input: n = %s, present = %s, future = %s, hierarchy = %s, budget = %s",
                         n, present, future, hierarchy, budget)

            retVal = pSolution.maxProfit(n, present, future, hierarchy, budget)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
