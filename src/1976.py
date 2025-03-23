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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def countPaths(self, n: int, roads: List[List[int]]) -> int:
        retVal = 0

        # Build adjacency list
        adjacency = [[] for _ in range(n)]
        for start_node, end_node, travel_time in roads:
            adjacency[start_node].append((end_node, travel_time))
            adjacency[end_node].append((start_node, travel_time))

        # Min-Heap (priority queue) for Dijkstra
        minHeap = [(0, 0)]  # (time, node)

        # Store shortest time to each node
        shortestTime = [float("inf")] * n
        shortestTime[0] = 0  # Distance to source is 0

        # Number of ways to reach each node in shortest time
        pathCount = [0] * n
        pathCount[0] = 1  # 1 way to reach node 0

        while minHeap:
            currTime, currNode = heappop(minHeap)

            # Skip outdated distances
            if currTime > shortestTime[currNode]:
                continue

            for neighbor_node, roadTime in adjacency[currNode]:
                # Found a new shortest path → Update shortest time and reset path count
                if currTime + roadTime < shortestTime[neighbor_node]:
                    shortestTime[neighbor_node] = currTime + roadTime
                    pathCount[neighbor_node] = pathCount[currNode]
                    heappush(minHeap, (shortestTime[neighbor_node], neighbor_node))
                # Found another way with the same shortest time → Add to path count
                elif currTime + roadTime == shortestTime[neighbor_node]:
                    pathCount[neighbor_node] = (pathCount[neighbor_node] + pathCount[currNode]) % self.MODULO

        retVal = pathCount[n - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, roads in zip(
            [7, 2],
            [[[0, 6, 7], [0, 1, 2], [1, 2, 3], [1, 3, 3], [6, 3, 3], [3, 5, 1], [6, 5, 1], [2, 5, 1], [0, 4, 5], [4, 6, 2]],
             [[1, 0, 10]]]
        ):
            # /* Example
            #  *  Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
            #  *  Output: 4
            #  *
            #  *  Input: n = 2, roads = [[1,0,10]]
            #  *  Output: 1
            #  */
            logging.info("Input: n = %s, roads = %s", n, roads)

            retVal = pSolution.countPaths(n, roads)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
