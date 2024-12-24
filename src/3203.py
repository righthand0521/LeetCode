import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from math import ceil
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
    def buildAdjList(self, size: int, edges: list[list[int]]) -> list[list[int]]:
        retVal = [[] for _ in range(size)]

        for edge in edges:
            retVal[edge[0]].append(edge[1])
            retVal[edge[1]].append(edge[0])

        return retVal

    def findDiameter(self, adjList: list[list[int]], node: int, parent: int) -> tuple[int, int]:
        retVal = 0, 0

        maxDepth1 = 0
        maxDepth2 = 0
        diameter = 0
        for neighbor in adjList[node]:
            # Skip the parent to avoid cycles
            if neighbor == parent:
                continue

            # Recursively calculate the diameter and depth of the neighbor's subtree
            childDiameter, depth = self.findDiameter(adjList, neighbor, node)

            # Increment depth to include edge to neighbor
            depth += 1

            # Update the maximum diameter of the subtree
            diameter = max(diameter, childDiameter)

            # Update the two largest depths from the current node
            if depth > maxDepth1:
                maxDepth2 = maxDepth1
                maxDepth1 = depth
            elif depth > maxDepth2:
                maxDepth2 = depth

        # Update the diameter to include the path through the current node
        diameter = max(diameter, maxDepth1 + maxDepth2)

        # Return the diameter and the longest depth
        retVal = diameter, maxDepth1

        return retVal

    def minimumDiameterAfterMerge(self, edges1: List[List[int]], edges2: List[List[int]]) -> int:
        retVal = 0

        edges1Size = len(edges1) + 1
        adjList1 = self.buildAdjList(edges1Size, edges1)
        diameter1, _ = self.findDiameter(adjList1, 0, -1)

        edges2Size = len(edges2) + 1
        adjList2 = self.buildAdjList(edges2Size, edges2)
        diameter2, _ = self.findDiameter(adjList2, 0, -1)

        combinedDiameter = ceil(diameter1 / 2) + ceil(diameter2 / 2) + 1

        retVal = max(diameter1, diameter2, combinedDiameter)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for edges1, edges2 in zip([[[0, 1], [0, 2], [0, 3]], [[0, 1], [0, 2], [0, 3], [2, 4], [2, 5], [3, 6], [2, 7]]],
                                  [[[0, 1]], [[0, 1], [0, 2], [0, 3], [2, 4], [2, 5], [3, 6], [2, 7]]]):
            # /* Example
            #  *  Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
            #  *  Output: 3
            #  *
            #  *  Input: edges1=[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2=[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
            #  *  Output: 5
            #  */
            logging.info("Input: edges1 = %s, edges2 = %s", edges1, edges2)

            retVal = pSolution.minimumDiameterAfterMerge(edges1, edges2)
            logging.info("Output: %s", retVal)

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
