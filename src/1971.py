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
    def validPath(self, n: int, edges: List[List[int]], source: int, destination: int) -> bool:
        retVal = False

        adjacency = [[] for _ in range(n)]
        for src, dst in edges:
            adjacency[src].append(dst)
            adjacency[dst].append(src)

        bfsQueue = deque()
        bfsQueue.append(source)
        visited = [False] * n
        visited[source] = True
        while bfsQueue:
            vertex = bfsQueue.popleft()
            if vertex == destination:
                break

            for next in adjacency[vertex]:
                if visited[next] == False:
                    bfsQueue.append(next)
                    visited[next] = True

        retVal = visited[destination]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges, source, destination in zip(
                [3, 6], [[[0, 1], [1, 2], [2, 0]], [[0, 1], [0, 2], [3, 5], [5, 4], [4, 3]]], [0, 0], [2, 5]):
            # /* Example
            #  *  Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
            #  *  Output: true
            #  *
            #  *  Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
            #  *  Output: false
            #  */
            logging.info("Input: n = %s, edges = %s, source = %s, destination = %s", n, edges, source, destination)

            retVal = pSolution.validPath(n, edges, source, destination)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
