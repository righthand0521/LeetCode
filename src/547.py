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
    def __init__(self):
        self.method = 2

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, i: int, isConnected: List[List[int]], visited: List[int]):
        isConnectedSize = len(isConnected)

        for j in range(isConnectedSize):
            if isConnected[i][j] == 0:
                continue
            if j in visited:
                continue
            visited.append(j)
            self.dfs(j, isConnected, visited)

    def bfs(self, i: int, isConnected: List[List[int]], visited: List[int]):
        isConnectedSize = len(isConnected)

        bfsQueue = deque([i])
        visited.append(i)
        while bfsQueue:
            idx = bfsQueue.popleft()
            for j in range(isConnectedSize):
                if isConnected[idx][j] == 0:
                    continue
                if j in visited:
                    continue
                bfsQueue.append(j)
                visited.append(j)

    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        retVal = 0

        isConnectedSize = len(isConnected)

        visited = []
        for i in range(isConnectedSize):
            if i in visited:
                continue

            if self.method == 1:
                self.dfs(i, isConnected, visited)
            elif self.method == 2:
                self.bfs(i, isConnected, visited)

            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for isConnected in [[[1, 1, 0], [1, 1, 0], [0, 0, 1]], [[1, 0, 0], [0, 1, 0], [0, 0, 1]]]:
            # /* Example
            #  *  Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
            #  *  Output: 2
            #  *
            #  *  Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
            #  *  Output: 3
            #  */
            logging.info("Input: isConnected = %s", isConnected)

            retVal = pSolution.findCircleNum(isConnected)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
