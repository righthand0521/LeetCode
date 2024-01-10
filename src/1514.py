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
    def maxProbability(self, n: int, edges: List[List[int]], succProb: List[float], start: int, end: int) -> float:
        retVal = 0

        graph = defaultdict(list)
        for i, (u, v) in enumerate(edges):
            graph[u].append((v, succProb[i]))
            graph[v].append((u, succProb[i]))

        maxProb = [0.0] * n
        maxProb[start] = 1.0

        priorityQueue = [(-1.0, start)]
        while priorityQueue:
            curProb, curNode = heappop(priorityQueue)
            if curNode == end:
                retVal = -curProb
                break

            for nxtNode, pathProb in graph[curNode]:
                if -curProb * pathProb > maxProb[nxtNode]:
                    maxProb[nxtNode] = -curProb * pathProb
                    heappush(priorityQueue, (-maxProb[nxtNode], nxtNode))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges, succProb, start, end in zip([3, 3, 3],
                                                  [[[0, 1], [1, 2], [0, 2]], [
                                                      [0, 1], [1, 2], [0, 2]], [[0, 1]]],
                                                  [[0.5, 0.5, 0.2], [
                                                      0.5, 0.5, 0.3], [0.5]],
                                                  [0, 0, 0],
                                                  [2, 2, 2]):
            # /* Example
            #  *  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
            #  *  Output: 0.25000
            #  *
            #  *  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
            #  *  Output: 0.30000
            #  *
            #  *  Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
            #  *  Output: 0.00000
            #  */
            logging.info("Input: n = %s, edges = %s, succProb = %s, start = %s, end = %s",
                         n, edges, succProb, start, end)

            retVal = pSolution.maxProbability(n, edges, succProb, start, end)
            logging.info("Output: %.5f", retVal)

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
