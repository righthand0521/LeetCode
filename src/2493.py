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


class UnionFind:
    def __init__(self, n: int):
        self.parent = [-1] * n
        self.depth = [0] * n

    def find(self, node) -> int:
        retVal = 0

        while self.parent[node] != -1:
            node = self.parent[node]
        retVal = node

        return retVal

    def union(self, node1, node2) -> None:
        node1 = self.find(node1)
        node2 = self.find(node2)

        # If both nodes already belong to the same set, no action needed
        if node1 == node2:
            return

        # Union by rank (depth) to keep the tree balanced
        if self.depth[node1] < self.depth[node2]:
            node1, node2 = node2, node1
        self.parent[node2] = node1

        # If the depths are equal, increment the depth of the new root
        if self.depth[node1] == self.depth[node2]:
            self.depth[node1] += 1


class Solution:
    def getNumberOfGroups(self, adjacencyList, srcNode, n) -> int:
        retVal = 0

        bfsQueue = deque()
        bfsQueue.append(srcNode)
        layerSeen = [-1] * n
        layerSeen[srcNode] = 0
        while bfsQueue:
            bfsQueueSize = len(bfsQueue)
            for _ in range(bfsQueueSize):
                currentNode = bfsQueue.popleft()
                for neighbor in adjacencyList[currentNode]:
                    if layerSeen[neighbor] == -1:  # If neighbor hasn't been visited, assign it to the next layer
                        layerSeen[neighbor] = retVal + 1
                        bfsQueue.append(neighbor)
                        continue

                    # If the neighbor is already in the same layer, return -1 (invalid partition)
                    if layerSeen[neighbor] == retVal:
                        retVal = -1
                        return retVal
            retVal += 1

        return retVal

    def magnificentSets(self, n: int, edges: List[List[int]]) -> int:
        retVal = -1  # If invalid split, return -1

        # Build the adjacency list and apply Union-Find for each edge
        adjacencyList = [[] for _ in range(n)]
        uf = UnionFind(n)
        for edge in edges:
            adjacencyList[edge[0] - 1].append(edge[1] - 1)
            adjacencyList[edge[1] - 1].append(edge[0] - 1)
            uf.union(edge[0] - 1, edge[1] - 1)

        # For each node, calculate the maximum number of groups for its component
        numOfGroupsForComponent = {}
        for node in range(n):
            numberOfGroups = self.getNumberOfGroups(adjacencyList, node, n)
            if numberOfGroups == -1:
                return retVal

            rootNode = uf.find(node)
            numOfGroupsForComponent[rootNode] = max(numOfGroupsForComponent.get(rootNode, 0), numberOfGroups)

        # Calculate the total number of groups across all components
        retVal = sum(numOfGroupsForComponent.values())

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([6, 3], [[[1, 2], [1, 4], [1, 5], [2, 6], [2, 3], [4, 6]], [[1, 2], [2, 3], [3, 1]]]):
            # /* Example
            #  *  Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
            #  *  Output: 4
            #  *
            #  *  Input: n = 3, edges = [[1,2],[2,3],[3,1]]
            #  *  Output: -1
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.magnificentSets(n, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
