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
    def dfs(self, graph: List[List[int]], answer: List[List[int]], stk: List[int], x: int, n: int) -> None:
        if x == n:
            answer.append(stk[:])
            return

        for y in graph[x]:
            stk.append(y)
            self.dfs(graph, answer, stk, y, n)
            stk.pop()

    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
        retVal = []

        graphSize = len(graph)
        stk = [0]
        self.dfs(graph, retVal, stk, 0, graphSize - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for graph in [[[1, 2], [3], [3], []], [[4, 3, 1], [3, 2, 4], [3], [4], []]]:
            # /* Example
            #  *  Input: graph = [[1,2],[3],[3],[]]
            #  *  Output: [[0,1,3],[0,2,3]]
            #  *
            #  *  Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
            #  *  Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
            #  */
            logging.info("Input: graph = %s", graph)

            retVal = pSolution.allPathsSourceTarget(graph)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
