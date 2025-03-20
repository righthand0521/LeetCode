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
    def dfs(self, node, adjList, visited, components, componentId):
        retVal = -1  # Initialize the cost to the number that has only 1s in its binary representation

        components[node] = componentId  # Mark the node as part of the current component
        visited[node] = True
        for neighbor, weight in adjList[node]:
            retVal &= weight  # Update the component cost by performing a bitwise AND of the edge weights
            if visited[neighbor] == True:
                continue
            # Recursively calculate the cost of the rest of the component and accumulate it into currentCost
            retVal &= self.dfs(neighbor, adjList, visited, components, componentId)

        return retVal

    def minimumCost(self, n: int, edges: List[List[int]], query: List[List[int]]) -> List[int]:
        retVal = []

        # Create the adjacency list of the graph
        adjList = [[] for _ in range(n)]
        for edge in edges:
            adjList[edge[0]].append((edge[1], edge[2]))
            adjList[edge[1]].append((edge[0], edge[2]))

        visited = [False] * n

        # Array to store the component ID of each node
        components = [0] * n
        componentCost = []
        componentId = 0
        # Perform DFS for each unvisited node to identify components and calculate their costs
        for node in range(n):
            if visited[node] == True:
                continue
            # Get the component cost and mark all nodes in the component
            componentCost.append(self.dfs(node, adjList, visited, components, componentId))
            componentId += 1

        for q in query:
            start, end = q
            # If they are in the same component, return the precomputed cost for the component
            # Else they are in different components, return -1
            if components[start] == components[end]:
                retVal.append(componentCost[components[start]])
            else:
                retVal.append(-1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges, query in zip([5, 3],
                                   [[[0, 1, 7], [1, 3, 7], [1, 2, 1]], [[0, 2, 7], [0, 1, 15], [1, 2, 6], [1, 2, 1]]],
                                   [[[0, 3], [3, 4]], [[1, 2]]]):
            # /* Example
            #  *  Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
            #  *  Output: [1,-1]
            #  *
            #  *  Input: n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
            #  *  Output: [0]
            #  */
            logging.info("Input: n = %s, edges = %s, query = %s", n, edges, query)

            retVal = pSolution.minimumCost(n, edges, query)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
