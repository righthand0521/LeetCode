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
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        retVal = [list()]

        adjacencyList = [[] for _ in range(n)]
        indegree = [0 for _ in range(n)]
        for edge in edges:
            fromNode = edge[0]
            toNode = edge[1]
            adjacencyList[fromNode].append(toNode)
            indegree[toNode] += 1

        nodesWithZeroIndegree = [i for i in range(n) if indegree[i] == 0]

        topologicalOrder = []
        while nodesWithZeroIndegree:
            currentNode = nodesWithZeroIndegree.pop(0)
            topologicalOrder.append(currentNode)
            # Reduce indegree of neighboring nodes and add them to the queue if they have no more incoming edges
            for neighbor in adjacencyList[currentNode]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    nodesWithZeroIndegree.append(neighbor)

        # Initialize the result list and set list for storing ancestors
        retVal = [[] for _ in range(n)]
        ancestorsSetList = [set() for _ in range(n)]
        # Fill the set list with ancestors using the topological order
        for node in topologicalOrder:
            for neighbor in adjacencyList[node]:
                # Add immediate parent, and other ancestors.
                ancestorsSetList[neighbor].add(node)
                ancestorsSetList[neighbor].update(ancestorsSetList[node])
        # Convert sets to lists and sort them
        for i in range(n):
            retVal[i].extend(ancestorsSetList[i])
            retVal[i].sort()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([8, 5],
                            [[[0, 3], [0, 4], [1, 3], [2, 4], [2, 7], [3, 5], [3, 6], [3, 7], [4, 6]],
                             [[0, 1], [0, 2], [0, 3], [0, 4], [1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]]):
            # /* Example
            #  *  Input: n = 8, edgeList = [[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]
            #  *  Output: [[],[],[],[0,1],[0,2],[0,1,3],[0,1,2,3,4],[0,1,2,3]]
            #  *
            #  *  Input: n = 5, edgeList = [[0,1],[0,2],[0,3],[0,4],[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
            #  *  Output: [[],[0],[0,1],[0,1,2],[0,1,2,3]]
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.getAncestors(n, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
