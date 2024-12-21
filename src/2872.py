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
    def maxKDivisibleComponents(self, n: int, edges: List[List[int]], values: List[int], k: int) -> int:
        retVal = 1

        # Base case: if there are less than 2 nodes, return 1
        if n < 2:
            return retVal

        # Step 1: Build the graph
        graph = defaultdict(set)
        for node1, node2 in edges:
            graph[node1].add(node2)
            graph[node2].add(node1)

        # Step 2: Initialize the BFS queue with leaf nodes (nodes with only one connection)
        nodes = []
        for node, neighbors in graph.items():
            if len(neighbors) == 1:
                nodes.append(node)
        bfsQueue = deque(nodes)

        # Step 3: Process nodes in BFS order
        componentCount = 0
        while bfsQueue:
            currentNode = bfsQueue.popleft()

            # Find the neighbor node
            neighborNode = -1
            if graph[currentNode]:
                neighborNode = next(iter(graph[currentNode]))

            # Remove the edge between current and neighbor
            if neighborNode >= 0:
                graph[neighborNode].remove(currentNode)

            # Check divisibility of the current node's value
            if values[currentNode] % k == 0:
                componentCount += 1
            else:
                # Add current node's value to the neighbor
                values[neighborNode] += values[currentNode]

            # If the neighbor becomes a leaf node, add it to the BFS queue
            if (neighborNode >= 0) and (len(graph[neighborNode]) == 1):
                bfsQueue.append(neighborNode)

        retVal = componentCount

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges, values, k in zip(
            [5, 7],
            [[[0, 2], [1, 2], [1, 3], [2, 4]], [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6]]],
            [[1, 8, 1, 4, 4], [3, 0, 6, 1, 5, 2, 1]],
            [6, 3]
        ):
            # /* Example
            #  *  Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
            #  *  Output: 2
            #  *
            #  *  Input: n = 7, edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values = [3,0,6,1,5,2,1], k = 3
            #  *  Output: 3
            #  */
            logging.info("Input: n = %s, edges = %s, values = %s, k = %s", n, edges, values, k)

            retVal = pSolution.maxKDivisibleComponents(n, edges, values, k)
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
