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
        self.tree = []
        self.distanceFromBob = []
        self.amountSize = 0

    def dfs(self, sourceNode, parentNode, time, bob, amount):
        retVal = 0

        # Find the node distances from Bob
        if sourceNode == bob:
            self.distanceFromBob[sourceNode] = 0
        else:
            self.distanceFromBob[sourceNode] = self.amountSize

        maxChild = float("-inf")
        for adjacentNode in self.tree[sourceNode]:
            if adjacentNode == parentNode:
                continue
            maxChild = max(maxChild, self.dfs(adjacentNode, sourceNode, time + 1, bob, amount))
            self.distanceFromBob[sourceNode] = min(
                self.distanceFromBob[sourceNode], self.distanceFromBob[adjacentNode] + 1)

        maxIncome = 0
        if self.distanceFromBob[sourceNode] > time:  # Alice reaches the node first
            maxIncome += amount[sourceNode]
        elif self.distanceFromBob[sourceNode] == time:  # Alice and Bob reach the node at the same time
            maxIncome += amount[sourceNode] // 2

        # Return max income of leaf node
        if maxChild == float("-inf"):
            retVal = maxIncome
        else:
            retVal = maxIncome + maxChild

        return retVal

    def mostProfitablePath(self, edges: List[List[int]], bob: int, amount: List[int]) -> int:
        retVal = 0

        self.amountSize = len(amount)

        self.tree = [[] for _ in range(self.amountSize)]
        for edge in edges:
            self.tree[edge[0]].append(edge[1])
            self.tree[edge[1]].append(edge[0])

        self.distanceFromBob = [0] * self.amountSize

        retVal = self.dfs(0, 0, 0, bob, amount)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for edges, bob, amount in zip([[[0, 1], [1, 2], [1, 3], [3, 4]], [[0, 1]]],
                                      [3, 1],
                                      [[-2, 4, 2, -4, 6], [-7280, 2350]]):
            # /* Example
            #  *  Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
            #  *  Output: 6
            #  *
            #  *  Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
            #  *  Output: -7280
            #  */
            logging.info("Input: edges = %s, bob = %s, amount = %s", edges, bob, amount)

            retVal = pSolution.mostProfitablePath(edges, bob, amount)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
