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
    def countCompleteComponents(self, n: int, edges: List[List[int]]) -> int:
        retVal = 0

        adjacency = [[] for _ in range(n)]
        for u, v in edges:
            adjacency[u].append(v)
            adjacency[v].append(u)

        visited = [False] * n

        for vertex in range(n):
            if visited[vertex] == True:
                continue
            visited[vertex] = True

            # BFS to find all vertices in the current component
            component = []
            bfsQueue = [vertex]
            while bfsQueue:
                current = bfsQueue.pop(0)
                component.append(current)

                # Process neighbors
                for neighbor in adjacency[current]:
                    if visited[neighbor] == True:
                        continue
                    bfsQueue.append(neighbor)
                    visited[neighbor] = True

            # Check if component is complete (all vertices have the right number of edges)
            isComplete = True
            for node in component:
                componentSize = len(component)
                adjacencyNodeSize = len(adjacency[node])
                if adjacencyNodeSize != componentSize - 1:
                    isComplete = False
                    break
            if isComplete == True:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([6, 6], [[[0, 1], [0, 2], [1, 2], [3, 4]], [[0, 1], [0, 2], [1, 2], [3, 4], [3, 5]]]):
            # /* Example
            #  *  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
            #  *  Output: 3
            #  *
            #  *  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
            #  *  Output: 1
            #  */
            logging.info("Input: n = %d, edges = %s", n, edges)

            retVal = pSolution.countCompleteComponents(n, edges)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
