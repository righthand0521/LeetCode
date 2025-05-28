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
    def dfs(self, node: int, parent: int, children: List[List[int]], k: int) -> int:
        retVal = 0

        if k < 0:
            return retVal

        retVal = 1
        for child in children[node]:
            if child == parent:
                continue
            retVal += self.dfs(child, node, children, k - 1)

        return retVal

    def build(self, edges: List[List[int]], k: int) -> List[int]:
        retVal = []

        edgesSize = len(edges) + 1
        children = [[] for _ in range(edgesSize)]
        for u, v in edges:
            children[u].append(v)
            children[v].append(u)

        retVal = [0] * edgesSize
        for i in range(edgesSize):
            retVal[i] = self.dfs(i, -1, children, k)

        return retVal

    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]], k: int) -> List[int]:
        retVal = []

        count1 = self.build(edges1, k)
        count2 = self.build(edges2, k - 1)
        maxCount2 = max(count2)

        edges1Size = len(edges1) + 1
        for i in range(edges1Size):
            retVal.append(count1[i] + maxCount2)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for edges1, edges2, k in zip(
            [[[0, 1], [0, 2], [2, 3], [2, 4]], [[0, 1], [0, 2], [0, 3], [0, 4]]],
            [[[0, 1], [0, 2], [0, 3], [2, 7], [1, 4], [4, 5], [4, 6]], [[0, 1], [1, 2], [2, 3]]],
            [2, 1]
        ):
            # /* Example
            #  *  Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
            #  *  Output: [9,7,9,8,8]
            #  *
            #  *  Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k = 1
            #  *  Output: [6,3,3,3,3]
            #  */
            logging.info("Input: edges1 = %s, edges2 = %s, k = %s", edges1, edges2, k)

            retVal = pSolution.maxTargetNodes(edges1, edges2, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
