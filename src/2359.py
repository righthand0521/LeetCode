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
    def dfs(self, node: int, edges: List[int], dist: List[int], visit: List[bool]) -> None:
        visit[node] = True

        neighbor = edges[node]
        if (neighbor != -1) and (visit[neighbor] == False):
            dist[neighbor] = 1 + dist[node]
            self.dfs(neighbor, edges, dist, visit)

    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        retVal = -1

        edgesSize = len(edges)

        dist1 = [float('inf')] * edgesSize
        dist1[node1] = 0
        visit1 = [False] * edgesSize
        self.dfs(node1, edges, dist1, visit1)

        dist2 = [float('inf')] * edgesSize
        dist2[node2] = 0
        visit2 = [False] * edgesSize
        self.dfs(node2, edges, dist2, visit2)

        minDist = float('inf')
        for currNode in range(edgesSize):
            if minDist > max(dist1[currNode], dist2[currNode]):
                retVal = currNode
                minDist = max(dist1[currNode], dist2[currNode])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for edges, node1, node2 in zip([[2, 2, 3, -1], [1, 2, -1]], [0, 0], [1, 2]):
            # /* Example
            #  *  Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
            #  *  Output: 2
            #  *
            #  *  Input: edges = [1,2,-1], node1 = 0, node2 = 2
            #  *  Output: 2
            #  */
            logging.info("Input: nums = %s, node1 = %s, node2 = %s", edges, node1, node2)

            retVal = pSolution.closestMeetingNode(edges, node1, node2)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
