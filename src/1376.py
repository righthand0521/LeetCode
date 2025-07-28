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
        self.method = 1

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, headID: int, adjacent: defaultdict[List[int]], informTime: List[int]) -> int:
        retVal = 0

        for node in adjacent[headID]:
            retVal = max(retVal, self.dfs(node, adjacent, informTime))
        retVal += informTime[headID]

        return retVal

    def bfs(self, headID: int, adjacent: defaultdict[List[int]], informTime: List[int]) -> int:
        retVal = 0

        bfsQueue = deque([(headID, 0)])
        while bfsQueue:
            id, minutes = bfsQueue.popleft()
            if len(adjacent[id]) == 0:
                retVal = max(retVal, minutes)
                continue
            for neighbor in adjacent[id]:
                bfsQueue.append((neighbor, minutes+informTime[id]))

        return retVal

    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        retVal = 0

        #
        adjacent = defaultdict(list)
        for employee in range(n):
            adjacent[manager[employee]].append(employee)
        # print(adjacent)

        #
        if self.method == 1:
            retVal = self.dfs(headID, adjacent, informTime)
        elif self.method == 2:
            retVal = self.bfs(headID, adjacent, informTime)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, headID, manager, informTime in zip(
            [1, 6],
            [0, 2],
            [[-1], [2, 2, -1, 2, 2, 2]],
            [[0], [0, 0, 1, 0, 0, 0]]
        ):
            # /* Example
            #  *  Input: n = 1, headID = 0, manager = [-1], informTime = [0]
            #  *  Output: 0
            #  *
            #  *  Input: n = 6, headID = 2, manager = [2,2,-1,2,2,2], informTime = [0,0,1,0,0,0]
            #  *  Output: 1
            #  */
            logging.info("n = %s, headID = %s, manager = %s, informTime = %s", n, headID, manager, informTime)

            retVal = pSolution.numOfMinutes(n, headID, manager, informTime)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
