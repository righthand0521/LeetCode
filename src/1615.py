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
    def maximalNetworkRank(self, n: int, roads: List[List[int]]) -> int:
        retVal = 0

        connect = [[0] * n for _ in range(n)]
        degree = [0] * n
        for a, b in roads:
            connect[a][b] = 1
            connect[b][a] = 1
            degree[a] += 1
            degree[b] += 1

        for i in range(n):
            for j in range(i + 1, n):
                rank = degree[i] + degree[j] - connect[i][j]
                retVal = max(retVal, rank)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, roads in zip([4, 5, 8],
                            [[[0, 1], [0, 3], [1, 2], [1, 3]],
                             [[0, 1], [0, 3], [1, 2], [1, 3], [2, 3], [2, 4]],
                             [[0, 1], [1, 2], [2, 3], [2, 4], [5, 6], [5, 7]]]):
            # /* Example
            #  *  Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
            #  *  Output: 4
            #  *
            #  *  Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
            #  *  Output: 5
            #  *
            #  *  Input: n = 8, roads = [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]
            #  *  Output: 5
            #  */
            logging.info("Input: n = %s, roads = %s", n, roads)

            retVal = pSolution.maximalNetworkRank(n, roads)
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
