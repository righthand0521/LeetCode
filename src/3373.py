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
    def dfs(self, node: int, parent: int, depth: int, children: List[List[int]], color: List[int]) -> int:
        retVal = 1 - depth % 2

        color[node] = depth % 2
        for child in children[node]:
            if child == parent:
                continue
            retVal += self.dfs(child, node, depth + 1, children, color)

        return retVal

    def build(self, edges: List[List[int]], color: List[int]) -> List[int]:
        retVal = []

        edgesSize = len(edges) + 1
        children = [[] for _ in range(edgesSize)]
        for u, v in edges:
            children[u].append(v)
            children[v].append(u)
        ret = self.dfs(0, -1, 0, children, color)
        retVal = [ret, edgesSize - ret]

        return retVal

    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        retVal = []

        edges1Size = len(edges1) + 1
        color1 = [0] * edges1Size
        count1 = self.build(edges1, color1)

        edges2Size = len(edges2) + 1
        color2 = [0] * edges2Size
        count2 = self.build(edges2, color2)

        retVal = [0] * edges1Size
        for i in range(edges1Size):
            retVal[i] = count1[color1[i]] + max(count2[0], count2[1])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for edges1, edges2 in zip(
            [[[0, 1], [0, 2], [2, 3], [2, 4]], [[0, 1], [0, 2], [0, 3], [0, 4]]],
            [[[0, 1], [0, 2], [0, 3], [2, 7], [1, 4], [4, 5], [4, 6]], [[0, 1], [1, 2], [2, 3]]]
        ):
            # /* Example
            #  *  Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
            #  *  Output: [8,7,7,8,8]
            #  *
            #  *  Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]]
            #  *  Output: [3,6,6,6,6]
            #  */
            logging.info("Input: edges1 = %s, edges2 = %s", edges1, edges2)

            retVal = pSolution.maxTargetNodes(edges1, edges2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
