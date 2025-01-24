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
    def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
        retVal = []

        graphSize = len(graph)

        indegree = [0] * graphSize
        adjacency = [[] for _ in range(graphSize)]
        for i in range(graphSize):
            for node in graph[i]:
                adjacency[node].append(i)
                indegree[i] += 1

        topologicalSortQueue = deque()
        for i in range(graphSize):
            if indegree[i] == 0:
                topologicalSortQueue.append(i)

        # Topological Sort Using Kahn's Algorithm
        safe = [False] * graphSize
        while topologicalSortQueue:
            node = topologicalSortQueue.popleft()
            safe[node] = True

            for neighbor in adjacency[node]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    topologicalSortQueue.append(neighbor)

        for i in range(graphSize):
            if safe[i] == True:
                retVal.append(i)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for graph in [[[1, 2], [2, 3], [5], [0], [5], [], []], [[1, 2, 3, 4], [1, 2], [3, 4], [0, 4], []]]:
            # /* Example
            #  *  Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
            #  *  Output: [2,4,5,6]
            #  *
            #  *  Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
            #  *  Output: [4]
            #  */
            logging.info("Input: graph = %s", graph)

            retVal = pSolution.eventualSafeNodes(graph)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
