import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


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
    def __init__(self):
        self.method = 1
        if self.method == 1:    # 1: Depth-First Search
            print("Depth-First Search")
        elif self.method == 2:  # 2: Breadth-First Search
            print("Breadth-First Search")
        print()

    def dfs(self, node: int, graph: List[List[int]], color: dict) -> bool:
        retVal = True

        for neighbor in graph[node]:
            if neighbor in color:
                if color[neighbor] == color[node]:
                    retVal = False
                    return retVal
            else:
                color[neighbor] = 1 - color[node]
                retVal = self.dfs(neighbor, graph, color)
                if retVal == False:
                    break

        return retVal

    def isBipartite(self, graph: List[List[int]]) -> bool:
        retVal = True

        color = {}
        graphSize = len(graph)
        for node in range(graphSize):
            if node in color:
                continue
            color[node] = 0

            if self.method == 1:    # 1: Depth-First Search
                retVal = self.dfs(node, graph, color)
                if retVal == False:
                    break
            elif self.method == 2:  # 2: Breadth-First Search
                bfsQueue = deque([node])
                while bfsQueue:
                    current = bfsQueue.popleft()
                    for neighbor in graph[current]:
                        if neighbor in color:
                            if color[neighbor] == color[current]:
                                retVal = False
                                return retVal
                        else:
                            color[neighbor] = 1 - color[current]
                            bfsQueue.append(neighbor)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for graph in [[[1, 2, 3], [0, 2], [0, 1, 3], [0, 2]], [[1, 3], [0, 2], [1, 3], [0, 2]]]:
            # /* Example
            #  *  Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
            #  *  Output: false
            #  *
            #  *  Input: graph = [[1,3],[0,2],[1,3],[0,2]]
            #  *  Output: true
            #  */
            logging.info("Input: graph = %s", graph)

            retVal = pSolution.isBipartite(graph)
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
