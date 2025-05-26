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
    def __init__(self):
        self.colorsOptions = 26  # colors consists of lowercase English letters.

    def largestPathValue(self, colors: str, edges: List[List[int]]) -> int:
        retVal = -1

        #
        colorsSize = len(colors)
        adjacent = defaultdict(list)
        indegree = [0] * colorsSize
        for x, y in edges:
            indegree[y] += 1
            adjacent[x].append(y)

        #
        colorsFound = 0
        colorsRecord = [[0] * self.colorsOptions for _ in range(colorsSize)]
        colorsQueue = deque()
        for i in range(colorsSize):
            if indegree[i] == 0:
                colorsQueue.append(i)

        while colorsQueue:
            u = colorsQueue.popleft()
            colorsRecord[u][ord(colors[u]) - ord("a")] += 1
            colorsFound += 1

            for v in adjacent[u]:
                indegree[v] -= 1

                for c in range(self.colorsOptions):
                    colorsRecord[v][c] = max(colorsRecord[v][c], colorsRecord[u][c])

                if indegree[v] == 0:
                    colorsQueue.append(v)

        #
        if colorsFound != colorsSize:
            return retVal

        retVal = 0
        for i in range(colorsSize):
            retVal = max(retVal, max(colorsRecord[i]))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for colors, edges in zip(["abaca", "a"], [[[0, 1], [0, 2], [2, 3], [3, 4]], [[0, 0]]]):
            # /* Example
            #  *  Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
            #  *  Output: 3
            #  *
            #  *  Input: colors = "a", edges = [[0,0]]
            #  *  Output: -1
            #  */
            logging.info("Input: colors = \"%s\", edges = %s", colors, edges)

            retVal = pSolution.largestPathValue(colors, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
