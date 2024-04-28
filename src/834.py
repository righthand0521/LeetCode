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
    def __init__(self) -> None:
        self.answer = None
        self.vertex = None
        self.adjacency = None
        self.distances = None

    def dfs(self, children: int, parent: int, depth: int) -> None:
        self.answer[0] += depth

        for neighnor in self.adjacency[children]:
            if neighnor != parent:
                self.dfs(neighnor, children, depth + 1)
                self.distances[children] += self.distances[neighnor]

    def reroot(self, children: int, parent: int) -> None:
        for neighnor in self.adjacency[children]:
            if neighnor != parent:
                self.answer[neighnor] = self.answer[children] + \
                    self.vertex - 2 * self.distances[neighnor]
                self.reroot(neighnor, children)

    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:
        retVal = []

        self.answer = [0] * n
        self.vertex = n
        self.adjacency = [[] for _ in range(n)]
        for x, y in edges:
            self.adjacency[x].append(y)
            self.adjacency[y].append(x)
        self.distances = [1] * n

        self.dfs(0, -1, 0)
        self.reroot(0, -1)
        retVal = self.answer

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([6, 1, 2], [[[0, 1], [0, 2], [2, 3], [2, 4], [2, 5]], [], [[1, 0]]]):
            # /* Example
            #  *  Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
            #  *  Output: [8,12,6,10,10,10]
            #  *
            #  *  Input: n = 1, edges = []
            #  *  Output: [0]
            #  *
            #  *  Input: n = 2, edges = [[1,0]]
            #  *  Output: [1,1]
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.sumOfDistancesInTree(n, edges)
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
