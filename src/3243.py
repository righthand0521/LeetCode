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
    def findMinDistance(self, adjacency: List[List[int]], n: int) -> int:
        retVal = 0

        dp = [0] * n
        dp[n - 1] = 0
        for currentNode in range(n - 2, -1, -1):
            minDistance = n
            for neighbor in adjacency[currentNode]:
                minDistance = min(minDistance, dp[neighbor] + 1)
            dp[currentNode] = minDistance
        retVal = dp[0]

        return retVal

    def shortestDistanceAfterQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        retVal = []

        adjacency = [[] for _ in range(n)]
        for i in range(n - 1):
            adjacency[i].append(i + 1)

        for src, dst in queries:
            adjacency[src].append(dst)
            retVal.append(self.findMinDistance(adjacency, n))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, queries in zip([5, 4], [[[2, 4], [0, 2], [0, 4]],  [[0, 3], [0, 2]]]):
            # /* Example
            #  *  Input: n = 5, queries = [[2,4],[0,2],[0,4]]
            #  *  Output: [3,2,1]
            #  *
            #  *  Input: n = 4, queries = [[0,3],[0,2]]
            #  *  Output: [1,1]
            #  */
            logging.info("Input: n = %s, queries = %s", n, queries)

            retVal = pSolution.shortestDistanceAfterQueries(n, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
