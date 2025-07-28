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
    def solver(self, x: str, y: str, graph: dict, visited: set) -> float:
        retVal = -1.0

        if x not in graph:
            return retVal

        if x == y:
            retVal = 1.0
            return retVal

        visited.add(x)
        for key, value in graph[x]:
            if key == y:
                retVal = value
                return retVal

        for key, value in graph[x]:
            if key not in visited:
                current = self.solver(key, y, graph, visited)
                if current != -1:
                    retVal = value * current
                    return retVal

        return retVal

    def calcEquation(self, equations: List[List[str]], values: List[float], queries: List[List[str]]) -> List[float]:
        retVal = []

        graph = defaultdict(set)
        for [u, v], val in zip(equations, values):
            graph[u].add((v, val))
            graph[v].add((u, 1/val))

        for x, y in queries:
            retVal.append(self.solver(x, y, graph, set()))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for graph, values, queries in zip(
            [[["a", "b"], ["b", "c"]],
             [["a", "b"], ["b", "c"], ["bc", "cd"]],
             [["a", "b"]]],
            [[2.0, 3.0],
             [1.5, 2.5, 5.0],
             [0.5]],
            [[["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"]],
             [["a", "c"], ["c", "b"], ["bc", "cd"], ["cd", "bc"]],
             [["a", "b"], ["b", "a"], ["a", "c"], ["x", "y"]]]
        ):
            # /* Example
            #  *  Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0],
            #  *  queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
            #  *  Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
            #  *
            #  *  Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
            #  *  queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
            #  *  Output: [3.75000,0.40000,5.00000,0.20000]
            #  *
            #  *  Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
            #  *  Output: [0.50000,2.00000,-1.00000,-1.00000]
            #  */
            logging.info(
                "Input: equations = %s, values = %s, queries = %s", graph, values, queries)

            retVal = pSolution.calcEquation(graph, values, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
