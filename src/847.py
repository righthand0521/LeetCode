import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


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
    def shortestPathLength(self, graph: List[List[int]]) -> int:
        retVal = 0

        graphSize = len(graph)

        bfsQueue = deque((i, 1 << i, 0) for i in range(graphSize))
        visited = {(i, 1 << i) for i in range(graphSize)}
        while bfsQueue:
            vertex, maskVertex, distance = bfsQueue.popleft()
            if maskVertex == (1 << graphSize) - 1:
                retVal = distance
                break

            for neighbor in graph[vertex]:
                maskNeighbor = maskVertex | (1 << neighbor)
                if (neighbor, maskNeighbor) not in visited:
                    bfsQueue.append((neighbor, maskNeighbor, distance + 1))
                    visited.add((neighbor, maskNeighbor))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for graph in [[[1, 2, 3], [0], [0], [0]], [[1], [0, 2, 4], [1, 3, 4], [2], [1, 2]]]:
            # /* Example
            #  *  Input: graph = [[1,2,3],[0],[0],[0]]
            #  *  Output: 4
            #  *
            #  *  Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
            #  *  Output: 4
            #  */
            logging.info("Input: points = %s", graph)

            retVal = pSolution.shortestPathLength(graph)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
