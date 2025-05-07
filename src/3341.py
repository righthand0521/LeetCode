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


class State:
    def __init__(self, x, y, distance) -> None:
        self.x = x
        self.y = y
        self.distance = distance

    def __lt__(self, other) -> bool:
        retVal = False

        if self.distance < other.distance:
            retVal = True

        return retVal


class Solution:
    def __init__(self) -> None:
        self.directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(moveTime)
        colSize = len(moveTime[0])

        dijkstra = [[float("inf")] * colSize for _ in range(rowSize)]
        dijkstra[0][0] = 0

        visit = [[0] * colSize for _ in range(rowSize)]

        queue = []
        heappush(queue, State(0, 0, 0))

        while queue:
            node = heappop(queue)
            if visit[node.x][node.y]:
                continue

            visit[node.x][node.y] = 1
            for dx, dy in self.directions:
                nextX = node.x + dx
                if (nextX < 0) or (nextX >= rowSize):
                    continue

                nextY = node.y + dy
                if (nextY < 0) or (nextY >= colSize):
                    continue

                distance = max(dijkstra[node.x][node.y], moveTime[nextX][nextY]) + 1
                if dijkstra[nextX][nextY] > distance:
                    dijkstra[nextX][nextY] = distance
                    heappush(queue, State(nextX, nextY, distance))

        retVal = dijkstra[rowSize - 1][colSize - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for moveTime in [[[0, 4], [4, 4]], [[0, 0, 0], [0, 0, 0]], [[0, 1], [1, 2]]]:
            # /* Example
            #  *  Input: moveTime = [[0,4],[4,4]]
            #  *  Output: 6
            #  *
            #  *  Input: moveTime = [[0,0,0],[0,0,0]]
            #  *  Output: 3
            #  *
            #  *  Input: moveTime = [[0,1],[1,2]]
            #  *  Output: 3
            #  */
            logging.info("Input: moveTime = %s", moveTime)

            retVal = pSolution.minTimeToReach(moveTime)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
