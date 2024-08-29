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
    def dfs(self, adjacencyList: List[List[int]], visited: List[int], stone: int) -> None:
        visited[stone] = True
        for neighbor in adjacencyList[stone]:
            if visited[neighbor] == False:
                self.dfs(adjacencyList, visited, neighbor)

    def removeStones(self, stones: List[List[int]]) -> int:
        retVal = 0

        stonesSize = len(stones)

        adjacencyList = [[] for _ in range(stonesSize)]
        for i in range(stonesSize):
            for j in range(i + 1, stonesSize):
                if (stones[i][0] == stones[j][0]) or (stones[i][1] == stones[j][1]):
                    adjacencyList[i].append(j)
                    adjacencyList[j].append(i)

        visited = [False] * stonesSize
        numOfConnectedComponents = 0
        for i in range(stonesSize):
            if visited[i] == False:
                self.dfs(adjacencyList, visited, i)
                numOfConnectedComponents += 1

        retVal = stonesSize - numOfConnectedComponents

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for stones in [
            [[0, 0], [0, 1], [1, 0], [1, 2], [2, 1], [2, 2]],
            [[0, 0], [0, 2], [1, 1], [2, 0], [2, 2]],
            [[0, 0]]
        ]:
            # /* Example
            #  *  Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
            #  *  Output: 5
            #  *
            #  *  Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
            #  *  Output: 3
            #  *
            #  *  Input: stones = [[0,0]]
            #  *  Output: 0
            #  */
            logging.info("Input: stones = %s", stones)

            retVal = pSolution.removeStones(stones)
            logging.info("Output: %d", retVal)

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
