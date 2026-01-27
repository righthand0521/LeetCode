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
    def minCost(self, n: int, edges: List[List[int]]) -> int:
        retVal = -1

        adjacency = [[] for _ in range(n)]
        for x, y, w in edges:
            adjacency[x].append((y, w))
            adjacency[y].append((x, 2 * w))

        distance = [float('inf')] * n
        distance[0] = 0
        visited = [False] * n
        heap = [(0, 0)]  # (Distance, Node)
        while heap:
            currentDistance, x = heappop(heap)
            if x == n - 1:
                retVal = currentDistance
                break

            if visited[x] == True:
                continue
            visited[x] = True

            for y, w in adjacency[x]:
                newDistance = currentDistance + w
                if newDistance < distance[y]:
                    distance[y] = newDistance
                    heappush(heap, (newDistance, y))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in [
            [4, [[0, 1, 3], [3, 1, 1], [2, 3, 4], [0, 2, 2]]],
            [4, [[0, 2, 1], [2, 1, 1], [1, 3, 1], [2, 3, 3]]]
        ]:
            # /* Example
            #  *  Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]
            #  *  Output: 5
            #  *
            #  *  Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]
            #  *  Output: 3
            #  */
            logging.info("Input: n = %d, edges = %s", n, edges)

            retVal = pSolution.minCost(n, edges)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
